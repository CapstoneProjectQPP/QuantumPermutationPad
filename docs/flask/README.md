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
### Notes
- Running `make all PORT={port}` will create a server in the background that will echo whatever it receives and the app on the port specified, `PORT=64999` by default
- You can kill any running processes on the port with `make clean` which will run `lsof | grep $(port) | awk '{print $2}' | xargs -I {} kill -9 {}`, although you should be careful not to kill any other programs which might be running
