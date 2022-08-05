import matplotlib.pyplot as plt
import numpy as np

'''
    read and print data
'''
def main():
    f = open('data.txt', 'r')

    # processing
    n_data = []
    start_data = []
    end_data = []
    while(True):
        line = f.readline()
        line = line.replace('\x1b[0m', '').replace('\x1b[1;33m', '').replace('\x1b[0m\x1b[1;33m', '')
        if(line == ''):
            break

        # process
        split_line = line.strip().split()[3:]
        n = split_line[0]
        start_mean = split_line[1]
        end_mean = split_line[2]

        # add
        n_data.append(n)
        start_data.append(start_mean)
        end_data.append(end_mean)
    
    f.close()

    n_data = np.array(n_data, dtype="int")
    start_data = np.array(start_data, dtype="float32")
    end_data = np.array(end_data, dtype="float32")
    
    # plotting
    plt.plot(n_data, start_data, color="red", label="starting cycle")
    plt.plot(n_data, end_data, color="blue", label="ending cycle")
    plt.locator_params(axis='y', nbins=6)
    plt.locator_params(axis='x', nbins=10)
    plt.title("cycle count when varying N eviction addresses for TLB")
    plt.xlabel("Num of eviction addresses")
    plt.ylabel("Cycles")
    plt.legend()
    plt.show()
    

if __name__ == '__main__':
    main()
