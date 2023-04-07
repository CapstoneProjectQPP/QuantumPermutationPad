#! /usr/bin/env python3

import sys
import os
import subprocess
import time
import threading
import socket
import logging
import base64
from flask import Flask, flash, render_template, request, redirect, send_file
from werkzeug.utils import secure_filename
from Client import *
from GI_interface import *

app = Flask(__name__)
algos = ['AES', 'QPP', 'AES & QPP']
tests = ['Encrypt', 'Encrypt & Decrypt', 'M.I.T.M',
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

logger = Logger.init(None, logging.INFO)
client = Client(GI_PORT, socket.gethostname(), "CLI")

task_id = 0


def allowed_file(filename):
    return '.' in filename and filename.split('.', 1)[1].lower() #in ALLOWED_EXTENSIONS


def check_equals(a, b):
    splitA = set(a.split("\n"))
    splitB = set(b.split("\n"))
    diff = splitB.difference(splitA)
    diff = ", ".join(diff)
    result = a==b
    logger.info("it is {} that the plain and cipher match".format(a == b))
    if not result:
        logger.error(a)
        logger.error(b)
    return result


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
           vector_num, vector_len, task_id, client, cipherpath, plainpath
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
            if file:
                file_extension = allowed_file(file.filename)
                filename = secure_filename(file.filename)
                file.save(os.path.join(app.config['DOWNLOAD_FOLDER'], filename))
                with open(os.path.abspath(DOWNLOAD_FOLDER + filename), 'rb') as fd:
                    content = fd.read()
                    test_vector.append(base64.b64encode(content).decode('ascii'))
        logger.debug("plainlist".center(40, '_'))
        logger.debug(test_vector)

        if test_select.find('Encrypt') != -1:
            logger.info("Encryption Begins")
            GI.Encrypt(task_id, test_vector, client)
            cipherlist = GI.ReceivedEncrypt(task_id, client)
            logger.info("plaintext".center(40, '_'))
            logger.info('\n'.join(cipherlist))
            logger.info("Encryption Ends")
            if test_select.find('Decrypt') != -1:
                logger.info("Decryption Begins")
                GI.Decrypt(task_id, cipherlist, client)
                plainlist = GI.ReceivedDecrypt(task_id, client)
                logger.info("ciphertext".center(40, '_'))
                logger.info('\n'.join(plainlist))
                logger.info("Decryption Ends")

        ciphertext = '\n'.join(cipherlist)
        plaintext = '\n'.join(test_vector)
        logger.debug("cipherlist".center(40, '_'))
        logger.debug(cipherlist)
        check_equals(plaintext, ciphertext)
        
        ciphertext = base64.b64decode(ciphertext)
        plaintext = base64.b64decode(plaintext)
        cipherpath = str(os.path.abspath(UPLOAD_FOLDER)) + '/' + \
                     str(task_id) + filename.split('.')[0] + '-ciphertext.' + file_extension

        plainpath = str(os.path.abspath(UPLOAD_FOLDER)) + '/' + \
            str(task_id) + filename.split('.')[0] + '-plaintext.' + file_extension

        with open(cipherpath, 'wb') as fd:
            fd.write(ciphertext)

        with open(plainpath, 'wb') as fd:
            fd.write(plaintext)

        task_id += 1

    return render_template('view.html', ciphertext=ciphertext,
                                        plaintext=plaintext,
                                        test=test_select,
                                        algo=algo_select
                                        )
                                        

@app.route("/download/cipher/")
def download_cipher():
    return send_file(cipherpath, as_attachment=True)


@app.route("/download/plain/")
def download_plain():
    return send_file(plainpath, as_attachment=True)


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
