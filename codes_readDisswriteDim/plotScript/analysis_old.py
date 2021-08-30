from functionsPlot import *
from parametersPlot import *

dir = '../../data_boxDim/DSCODE/'
save_dir='../../data_boxDim/DSCODE/'
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
D_q= np.array([0.0]*N_qMom)
C_q= np.array([0.0]*N_qMom)

dataR=read_file(dir+file,0)
spectrum=np.array([[0.0]*2]*N_qMom)
spectrum_sorted=np.array([[0.0]*2]*N_qMom)

# FINDING THE MOMENTS
for q in range(0,N_qMom):
    dataMom[:,q]=read_file(dir+file,q+1)
    if(qMom[q] < 0.0):
        dataExp[q],c=linregress(dataR[:N_Zfn-2],dataMom[:N_Zfn-2,q])
    else:
    	dataExp[q],c=linregress(dataR,dataMom[:,q])
    # print(qMom[q],dataExp[q])
q_star=4
for q in range(0,N_qMom):
    if(qMom[q] != 1.0):
        D_q[q]=dataExp[q]/(qMom[q]-1.0)
# To avoid Nan
    if(qMom[q] == 1.0):
        q_star=q
        D_q[q]=0.5*(D_q[q-1]+D_q[q+1])
# Taking average for D_1
C_q=(qMom-1.0)*(D_q-2.0)

dataExp_spl = interp1d(qMom,dataExp,kind='cubic')
D_q_spl = interp1d(qMom,D_q,kind='cubic')
if(qMom[q_star] == 1.0):
    D_q[q_star]=D_q_spl(qMom[q_star])
# Refitting D_1 from the spline
C_q_spl = interp1d(qMom,C_q,kind='cubic')

dx=1e-6
for q in range(1,N_qMom-1):
    h[q] =  derivative(C_q_spl,qMom[q],dx=dx)/3.0
    D_h[q] = 3.0*h[q]*qMom[q]-C_q_spl(qMom[q])+2.0 
    spectrum[q,0]=h[q]
    spectrum[q,1]=D_h[q]

q_L=qMom[0]+5*dx
q_R=qMom[N_qMom-1]-5*dx
h[0]=derivative(C_q_spl,q_L,dx=dx)/3.0
D_h[0] = 3.0*h[0]*q_L-C_q_spl(q_L)+2.0 
h[N_qMom-1]=derivative(C_q_spl,q_R,dx=dx)/3.0
D_h[N_qMom-1] = 3.0*h[N_qMom-1]*q_R-C_q_spl(q_R)+2.0 

spectrum_sorted=spectrum[np.argsort(spectrum[:,0])]	

dataOut=np.column_stack((qMom,dataExp,D_q,C_q))
np.savetxt(save_dir+'exponents_py.dat',dataOut,fmt=('%10.6f','%30.15f','%30.15f','%30.15f') )

dataOut=np.column_stack((h,D_h))
np.savetxt(save_dir+'spectrum_py.dat',dataOut,fmt=('%10.6f','%20.15f') )

