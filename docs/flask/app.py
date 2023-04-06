#! /usr/bin/env python3

import os
from flask import Flask, flash, render_template, request, redirect, session
from werkzeug.utils import secure_filename
from Client import *
from GI_interface import *

app = Flask(__name__)
algos = ['AES', 'QPP', 'AES & QPP']
tests = ['Encryption', 'Decryption',
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

client = Client(GI_PORT, socket.gethostname(), "CLI")

task_id = 0


def allowed_file(filename):
    return '.' in filename and \
        filename.split('.', 1)[1].lower() in ALLOWED_EXTENSIONS


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
        print("ERROR 1")
        vector_select = request.form['vector_select']

    return render_template('calc.html',
                           algo_list=algos,
                           test_list=tests,
                           vector_select=vector_select)


@app.route("/view/", methods=['GET', 'POST'])
def view():
    global vector_select, algos, tests, vector_num, vector_len, task_id, client
    test = algo = "ERROR"
    test_vector = []

    if request.method == 'POST':
        algo_select = request.form.get('algo_select')
        test_select = request.form.get('test_select')
        print("ERROR 2")
        print("{}, {}".format(algo_select, test_select))
        if vector_select == "True":
            print("ERROR 3")
            vector_len = request.form["vector_len"]
            vector_num = request.form["vector_num"]
            print("{} vectors of size {}".format(vector_num, vector_len))
            test_vector = Commands.test_vector_gen([int(vector_len), int(vector_num)])
        else:
            print("ERROR 4")
            if 'file' not in request.files:
                flash("No File Uploaded")
            file = request.files['file']
            if file.filename == '':
                flash("No File Selected")
            if file and allowed_file(file.filename):
                filename = secure_filename(file.filename)
                file.save(os.path.join(app.config['DOWNLOAD_FOLDER'], filename))
                with open(os.path.abspath(DOWNLOAD_FOLDER + filename), 'r') as fd:
                    while True:
                        line = fd.readline()
                        if not line:
                            break
                        test_vector.append(line)
                print("{}, contents:\n{}".format(filename, test_vector))
        GI.Encrypt(task_id, test_vector, client)
        print("Going into Recieve")
        client.to_outgoing_queue("Please Help\n")
        client.connection_send()
        cipherlist = GI.ReceivedEncrypt(task_id, client)
        print("cipherlist: \n" + cipherlist)
        task_id += 1

    return render_template('view.html', test=test_select, algo=algo_select)


if __name__ == "__main__":
    app.config['DOWNLOAD_FOLDER'] = os.path.abspath(DOWNLOAD_FOLDER)
    app.secret_key = 'secret_key'
    app.config['SESSION_TYPE'] = 'filesystem'
    client.connection_setup()
    app.run(debug=False, host=socket.gethostname(), port=4996)
    client.s.close()
