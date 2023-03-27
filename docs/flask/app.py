from flask import Flask, render_template

app = Flask(__name__)
algos = ['AES', 'QPP', 'AES & QPP']
tests = ['Encryption', 'Decryption',
         'Encrypt & Decrypt', 'M.I.T.M',
         'Brute Force', 'Monte Carlo',
         'Multi-block Message', 'Known Answer'
         ]


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


@app.route("/calc/")
def calc():
    return render_template('calc.html', algo_list=algos, test_list=tests)


@app.route("/view/")
def view():
    return render_template('view.html')
