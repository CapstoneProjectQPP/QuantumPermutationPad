CC=@
PORT=64999

all:
	$(CC) ./server.py $(PORT) &
	$(CC) ./app.py $(PORT)
	
# This is to remove any processes on the port 
clean:
	lsof | grep $(PORT) | awk '{print $$2}' | head -n 1 | xargs -I {} kill -9 {} 
	rm uploads/*.txt -r
