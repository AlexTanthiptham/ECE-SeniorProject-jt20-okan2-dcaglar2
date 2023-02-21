from bluedot.btcomm import BluetoothServer
from signal import pause
import json
import os
import time
import datetime
LOG_DIRECTORY = "Log"
log = []
start = int(time.time())


def getFilePath(filename: str) -> str:
    return os.path.join(os.path.join(os.getcwd(), LOG_DIRECTORY), filename)


def unixTimeToString(unix_time):
    """Convert a Unix timestamp to a string in the format 'dd-MM-yyyy-hh-mm'."""
    # Convert Unix time to a datetime object
    dt = datetime.datetime.fromtimestamp(unix_time)
    # Format the datetime object as a string
    dt_str = dt.strftime('%d-%m-%Y-%H-%M')
    return dt_str


def data_received(data):
    global start
    try:
        cleanData = json.loads(data)
        os.system('clear')
        print(cleanData)
        log.append(cleanData)
        with open(getFilePath(f"{unixTimeToString(start)}_log.json"), "w") as f:
            json.dump({f"{start}": log}, f)
    except Exception as err:
        print(err)
    # data = cleanData
    # s.send(data)


def connected():
    global start
    start = int(time.time())
    print(f"connected")

print("starting")
s = BluetoothServer(
    data_received, when_client_connects=connected, encoding="UTF-8")
# s.decode = decoder


pause()
print("after pause")
