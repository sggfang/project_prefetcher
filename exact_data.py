import os

written_lines = []

def main(data_path):
		tifs = {}
		tifs_lat = {}
		tifs_rate = {}
		baseline = {}
		baseline_lat = {}
		baseline_rate = {}
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
										elif "icache.overall_miss_latency" in line:
												baseline_lat[bench] = float(line.split()[1])
										elif "icache.overall_miss_rate" in line:
												baseline_rate[bench] = float(line.split()[1])
				elif "tifs" in folder:
						with open(file_path, 'r') as file:
								readlines = file.readlines()
								for line in readlines:
										if "ipc" in line:
												tifs[bench] = float(line.split()[1])
										elif "icache.overall_miss_latency" in line:
												tifs_lat[bench] = float(line.split()[1])
										elif "icache.overall_miss_rate" in line:
												tifs_rate[bench] = float(line.split()[1])
		wins = []
		ipc_ave = 0
		ipc_max = 0
		lat_ave = 0
		lat_max = 0
		rate_ave = 0
		rate_max = 0
		for k in baseline.keys():
				if baseline[k] < tifs[k]:
						wins.append(k)
		for k in wins:
				# print(k, str(100*(tifs[k]-baseline[k])/baseline[k])+"%"
				ipc_diff = 100*(tifs[k]-baseline[k])/baseline[k]
				miss_lat_diff = 100*(tifs_lat[k]-baseline_lat[k])/baseline_lat[k]
				miss_rate_diff = 100*(tifs_rate[k]-baseline_rate[k])/baseline_rate[k]
				if ipc_max < ipc_diff:
						ipc_max = ipc_diff
				ipc_ave += ipc_diff
				if lat_max > miss_lat_diff:
						lat_max = miss_lat_diff
				lat_ave += miss_lat_diff
				if rate_max > miss_rate_diff:
						rate_max = miss_rate_diff
				rate_ave += miss_rate_diff
				written_lines.append(k+": (ipc_diff, "+str(ipc_diff)
															+"%); (miss_latency_diff, "+str(miss_lat_diff)
															+"%); (miss_rate, "+str(miss_rate_diff)+"%\n")
		written_lines.append("ipc_max: "+str(ipc_max)+"; ipc_ave: "+str(ipc_ave/len(wins))+"\n")
		written_lines.append("lat_max: "+str(lat_max)+"; lat_ave: "+str(lat_ave/len(wins))+"\n")
		written_lines.append("rate_max: "+str(rate_max)+"; rate_ave: "+str(rate_ave/len(wins))+"\n")


if __name__ == '__main__':
		for folder in os.listdir(os.getcwd()):
				if not folder.startswith("data"):
						continue
				# print(folder+":")
				written_lines.append(folder+":\n")
				main(os.path.join(os.getcwd(), folder))
				written_lines.append("\n")
		with open("ipc.txt", 'w') as file:
				file.writelines(written_lines)

