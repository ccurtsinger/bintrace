
class part2:
	def __init__(self, default=None, opsize=None, rex=None):
		if default == None:
			self.default = 0
		else:
			self.default = default
			
		if opsize == None:
			self.opsize = self.default
		else:
			self.opsize = opsize
			
		if rex == None:
			self.rex = self.default
		else:
			self.rex = rex

a = part2(4, 2)
b = part2(1)

