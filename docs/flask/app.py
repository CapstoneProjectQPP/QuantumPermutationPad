#! /usr/bin/env python3

import sys
import os
import subprocess
import time
import threading
import socket
import logging
from flask import Flask, flash, render_template, request, redirect, send_file
from werkzeug.utils import secure_filename
from Client import *
from GI_interface import *

app = Flask(__name__)
algos = ['AES', 'QPP', 'AES & QPP']
tests = ['Encrypt', 'Decrypt',
         'Encrypt & Decrypt', 'M.I.T.M',
         'Brute Force', 'Monte Carlo',
         'Multi-block Message', 'Known Answer'
         ]
DOWNLOAD_FOLDER = "downloads/"
UPLOAD_FOLDER = "uploads/"
ALLOWED_EXTENSIONS = {'txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif'}
GI_PORT = 64999

vector_select = "True"
vector_len = 100
vector_num = 100

logger = Logger.init(None, logging.ERROR)
client = Client(GI_PORT, socket.gethostname(), "CLI")

task_id = 0


def allowed_file(filename):
    return '.' in filename and filename.split('.', 1)[1].lower() #in ALLOWED_EXTENSIONS


@app.route("/")
@app.route("/index/")
def index():
    return render_template('index.html')


@app.route("/api/")
def api():
    return render_template('api.html')


@app.route("/research/")
def research():
    return render_template('research.html')


@app.route("/demo/")
def demo():
    return render_template('demo.html')


@app.route("/calc/", methods=['GET', 'POST'])
def calc():
    global vector_select, algos, tests, vector_num, vector_len
    if request.method == "POST":
        vector_select = request.form['vector_select']

    return render_template('calc.html',
                           algo_list=algos,
                           test_list=tests,
                           vector_select=vector_select)


@app.route("/view/", methods=['GET', 'POST'])
def view():
    global vector_select, algos, tests, logger, \
           vector_num, vector_len, task_id, client, cipherpath
    test = algo = "ERROR"
    test_vector = []
    client.clear_queue()
    if request.method == 'POST':
        algo_select = request.form.get('algo_select')
        test_select = request.form.get('test_select')
        logger.info("{}, {}".format(algo_select, test_select))
        if vector_select == "True":
            vector_len = request.form["vector_len"]
            vector_num = request.form["vector_num"]
            logger.info("{} vectors of size {}".format(vector_num, vector_len))
            test_vector = Commands.test_vector_gen([int(vector_len), int(vector_num)])
        else:
            if 'file' not in request.files:
                logger.error("FILE NOT UPLOADED")
            file = request.files['file']
            if file.filename == '':
                logger.error("FILE NOT VALID")
            if file and allowed_file(file.filename):
                filename = secure_filename(file.filename)
                file.save(os.path.join(app.config['DOWNLOAD_FOLDER'], filename))
                with open(os.path.abspath(DOWNLOAD_FOLDER + filename), 'r') as fd:
                    while True:
                        line = fd.readline()
                        if not line:
                            break
                        test_vector.append(line)
        logger.info("plainlist".center(40, '_'))
        logger.info(test_vector)

        GI.Encrypt(task_id, test_vector, client)
        cipherlist = GI.ReceivedEncrypt(task_id, client)

        ciphertext = '\n'.join(cipherlist)
        logger.info("cipherlist".center(40, '_'))
        logger.info(cipherlist)
        cipherpath = str(os.path.abspath(UPLOAD_FOLDER)) + '/' + \
                     str(task_id) + '-ciphertext.txt'

        with open(cipherpath, 'w') as fd:
            fd.write(ciphertext)
        task_id += 1

    return render_template('view.html', ciphertext=ciphertext,
                                        test=test_select,
                                        algo=algo_select
                                        )
                                        

@app.route("/download/")
def download_cipher():
    return send_file(cipherpath, as_attachment=True)


if __name__ == "__main__":
    global GI_interface
    app.config['DOWNLOAD_FOLDER'] = os.path.abspath(DOWNLOAD_FOLDER)
    app.secret_key = 'secret_key'
    app.config['SESSION_TYPE'] = 'filesystem'
    GI_interface = sys.argv[1]

    try:
        client.connection_setup()

    except:
        command = "nc -l " + str(GI_PORT) + " &"
        subprocess.call(command, shell=True)
        time.sleep(5)
        client.connection_setup()

    finally:
        incoming_t = threading.Thread(target=client.connection_recv, args=())
        outgoing_t = threading.Thread(target=client.connection_send, args=())
        incoming_t.start()
        outgoing_t.start()

        app.run(debug=False, host=socket.gethostname(), port=4996)

        incoming_t.join()
        outgoing_t.join()
        client.s.close()
