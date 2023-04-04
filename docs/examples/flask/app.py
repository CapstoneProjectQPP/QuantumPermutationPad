from markupsafe import escape
import os
from flask import Flask, render_template, request, \
    url_for, flash, redirect, abort

app = Flask(__name__)
app.config['SECRET_KEY'] = os.urandom(24).hex()
algos = ['AES', 'QPP', 'Both']
tests = ['Encryption', 'Decryption',
         'Encrypt & Decrypt', 'M.I.T.M',
         'Brute Force', 'Monte Carlo',
         'Known Answer', 'Multi-block Message']


@app.route('/index/')
@app.route('/')
def index():
    return render_template('index.html')


@app.route('/api/')
def api():
    return render_template('api.html')


@app.route('/research/')
def research():
    return render_template('research.html')


@app.route('/demo/')
def demo():
    return render_template('demo.html')


@app.route('/calc/', methods=['GET', 'POST'])
def calc():
    if request.method == 'POST':
        test_parameters = [None, None, None, None]
        tag = None

        test_parameters[0] = request.form.get('num')
        test_parameters[1] = request.form.get('len')
        test_parameters[2] = request.form.get('algo_select')
        test_parameters[3] = request.form.get('test_select')

        if request.form.get("log"):
            tag += 'l'

        if request.form.get("verbose"):
            tag += 'v'

        data = test_parameters[0]

        for i in range(1, 4):
            if test_parameters[i] is not None:
                data += "+" + test_parameters[i]
        return redirect("/view/{}".format(data))
    else:
        return render_template('calc.html', algos=algos, tests=tests)


@app.route('/view/<int:num>+<int:len>+<algo_type>+<test_type>',
           methods=['GET', 'POST'])
def view(num, len, algo_type, test_type):
    return render_template('view.html', data=[num, len, algo_type,
                                              test_type])


if __name__ == '__main__':
    app.run(debug=True)









@app.route('/capitalize/<word>/')
def capitalize(word):
    return "<h3>{}</h3>".format(escape(word.capitalize()))


@app.route('/add/<int:n1>/<int:n2>')
def add(n1, n2):
    return "<h1>{}</h1>".format(n1 + n2)


@app.route('/users/<int:user_id>')
def greet_user(user_id):
    users = ["Bob", "Kelly", "John"]
    try:
        return "<h2>Hello {}</h2>".format(users[user_id])
    except IndexError:
        abort(404)
