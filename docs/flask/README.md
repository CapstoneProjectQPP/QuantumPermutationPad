## Setup to run Flask

1. In flask directory, create and run virtual enviroment by running these commands 
```
python3 -m venv venv 
. venv/bin/activate
```

2. Install Flask using command `pip install Flask` other dependiences may be required
3. Set Flask application with command `export FLASK_APP=app`
4. Then set mode of operation to either `export FLASK_ENV=development` or `export FLASK_ENV=production`
5. Run website with command `./app.py` and the website should be at address `http://{hostname}:4996/` loaded on the home page
6. There is a sample server.py program which will send whatever it receives from the app `./server.py $(port)`
7. You can kill any running processes on the port by running the command `lsof | grep $(port) | awk '{print $2}' | xargs -I {} kill -9 {}`

