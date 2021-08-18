from functionsPlot import *
from parametersPlot import *

dir = '../'
file = 'moment_details.dat'

qMom = np.loadtxt(dir+file)
N_qMom=np.size(qMom)
file = 'levels_of_partition.dat'
lev = read_file(dir+file,0)
N_Zfn = np.size(lev)
file = 'partition_function.dat'
dataMom = np.array([[0.0]*N_qMom]*N_Zfn)
dataR = np.array([0.0]*N_Zfn)
dataExp= np.array([0.0]*N_qMom)
f_spl= np.array([0.0]*N_qMom)
h= np.array([0.0]*N_qMom)
D_h= np.array([0.0]*N_qMom)
dataR=read_file(dir+file,0)
for q in range(0,N_qMom):
    dataMom[:,q]=read_file(dir+file,q+1)
    dataExp[q],c=linregress(dataR,dataMom[:,q])
    # print(qMom[q],dataExp[q])

f_spl = interp1d(qMom,dataExp,kind='cubic')
for q in range(1,N_qMom-1):
    h[q] =  (derivative(f_spl,qMom[q],dx=1e-6)-2.0 )/3.0
    D_h[q] = (3.0 * h[q] + 2.0 )* qMom[q] +3 - dataExp[q]
    print(h[q],D_h[q])
