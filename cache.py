import json

class CacheManager():
	def __init__(self):
		self.cache = {}
		self.readCache()
	def readCache(self):
		with open("cache.json","r") as f:
			self.cache = json.load(f)
		print("\033[1;1m CACHE LOADED \033[0m")
	def writeCache(self):
		with open("cache.json","w") as f:
			json.dump(self.cache,f)
		print("\033[1;1m CACHE SAVED \033[0m")
	def getCacheData(self):
		return self.cache
	def getFocalLength(self):
		return self.cache.get("focal")
	def getKinectDistanceCal(self):
		return self.cache.get("kdc")
	def getTiltAngle(self):
		return self.cache.get("tiltAngleRad")
	def setFocalLength(self,fl):
		self.cache["focal"] = fl
	def setKinectDistanceCal(self,kdc):
		self.cache["kdc"] = kdc
	def setTiltAngle(self,ta):
		self.cache["tiltAngleRad"] = ta	
		
		
