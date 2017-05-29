import re


def match_enzymes(strand,names,sequences):
	pos=[]
	for each in zip(names,sequences):
		var = [temp.start() for temp in re.finditer(each[1], strand)]
		if var:
			tup = (each[0], var)
			pos.append(tup)
	return pos


res= match_enzymes("GCTGACGCGG", ["HgaI"], ["GACGC"])
res= match_enzymes("GGCCGAGGCCTCGAGGCC", ["HaeIII"], ["GGCC"])
res= match_enzymes("ATTGCGAGCT", ["AluI", "KpnI"], ["AGCT", "AGCT"])
print res