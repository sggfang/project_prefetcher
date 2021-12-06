import os

written_lines = []

def main(data_path):
		tifs = {}
		baseline = {}
		for folder in os.listdir(data_path):
				params = folder.split('_')
				if len(params) != 3:
						continue
				bench = params[-1]
				file_path = os.path.join(data_path, folder, "stats.txt")
				if "baseline" in folder or "stride" in folder:
						with open(file_path, 'r') as file:
								readlines = file.readlines()
								for line in readlines:
										if "ipc" in line:
												baseline[bench] = float(line.split()[1])
				elif "tifs" in folder:
						with open(file_path, 'r') as file:
								readlines = file.readlines()
								for line in readlines:
										if "ipc" in line:
												tifs[bench] = float(line.split()[1])

		wins = []
		for k in baseline.keys():
				if baseline[k] < tifs[k]:
						wins.append(k)
		for k in wins:
				print(k, baseline[k], tifs[k], 
							str(100*(tifs[k]-baseline[k])/baseline[k])+"%")
				written_lines.append(k+": "+str(100*(tifs[k]-baseline[k])/baseline[k])+"%\n")


if __name__ == '__main__':
		for folder in os.listdir(os.getcwd()):
				if not folder.startswith("data"):
						continue
				print(folder+":")
				written_lines.append(folder+":\n")
				main(os.path.join(os.getcwd(), folder))
		with open("ipc.txt", 'w') as file:
				file.writelines(written_lines)

