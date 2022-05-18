import csv
def parse(file, out):
    readin = open(file, 'r')
    rd = csv.reader(readin, delimiter=' ')
    output = open(out, 'a')
    for line in rd:
        if line[0].find("\t") == -1:
            l = line[0].split(" ")
        else:
            l = line[0].split("\t") 
        to_add = l[0] + ',' + l[1] + '\n'
        output.write(to_add)
    readin.close()
    output.close()

parse("./data/links.tsv", "./data/parsed.txt")

