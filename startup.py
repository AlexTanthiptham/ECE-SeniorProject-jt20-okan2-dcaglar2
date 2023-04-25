import subprocess as sb
from time import sleep

def runCmd(cmd:list):
	p = sb.Popen(cmd,stdout=sb.DEVNULL)
	sleep(1)
	isOff = p.poll()
	while not isOff:
		p.kill()
		sleep(1)
		isOff = p.poll()
		print(isOff)
	
def runMicFix():
	cmd= ["freenect-micview"]
	runCmd(cmd)

if __name__ == "__main__":
	runMicFix()
