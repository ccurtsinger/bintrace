from x86 import primary

class inst:
	def __init__(self):
		self.mnemonic = 'Undecoded'
		self.operands = []
		self.prefixes = []
		
	def __str__(self):
		result = ''
		
		for p in self.prefixes:
			result += p + ' '
		
		result += self.mnemonic + ' '
		
		result += ', '.join(map(str, self.operands))
		
		return result

def decode(bytes):
	try:
		while True:
			i = inst()
	
			done = False
			table = primary
	
			while not done:
				b = bytes.next()
				print 'decoding', b, 'with', table[b]
				(done, table) = table[b](i, b, bytes)

			print i
	except StopIteration as stop:
		print 'End of stream'
