from functionsPlot import *
from parametersPlot import *

dir = '../../data_boxDim/DSCODE/'
save_dir='../../data_boxDim/DSCODE/'

# List of moments
file = 'moment_details.dat'
qMom = np.loadtxt(dir+file)
N_qMom=np.size(qMom)

# List of partition
file = 'levels_of_partition.dat'
lev = read_file(dir+file,0)
N_Zfn = np.size(lev)

# Parition fucntion
file = 'partition_function.dat'
dataMom = np.array([[0.0]*N_qMom]*N_Zfn)
dataR = np.array([0.0]*N_Zfn)
dataExp= np.array([0.0]*N_qMom)
dataExp_spl= np.array([0.0]*N_qMom)
D_q= np.array([0.0]*N_qMom)
alp= np.array([0.0]*N_qMom)
h= np.array([0.0]*N_qMom)
f_h= np.array([0.0]*N_qMom)
spectrum=np.array([[0.0]*2]*N_qMom)
spectrum_sorted=np.array([[0.0]*2]*N_qMom)

# FINDING THE MOMENTS
dataR=read_file(dir+file,0)
for q in range(0,N_qMom):
    dataMom[:,q]=read_file(dir+file,q+1)
    if(qMom[q] < 0.0):
        dataExp[q],c=linregress(dataR[:],dataMom[:,q])
    else:
    	dataExp[q],c=linregress(dataR[:],dataMom[:,q])
    D_q[q]=dataExp[q]/(qMom[q]-1.0)

# SPLINE INTERPOLATION
dataExp_spl = interp1d(qMom,dataExp,kind='cubic')

# FINDING THE DERIVATIVE TO FIND FRACTAL DIMENSION FOR EACH h
dx=1e-4
dne=0.0
for q in range(1,N_qMom-1):
    dne =  derivative(dataExp_spl,qMom[q],dx=dx)
    f_h[q] = dne*qMom[q]+3.0-dataExp_spl(qMom[q])
    alp[q] = dne - 3
    h[q] = (dne-2.0)/3.0
    spectrum[q,0]=h[q]
    spectrum[q,1]=f_h[q]

# END POINTS
q_L=qMom[0]+5*dx
q_R=qMom[N_qMom-1]-5*dx

dne =  derivative(dataExp_spl,q_L,dx=dx)
D_max = dne
f_h[0] = dne*q_L+3.0-dataExp_spl(q_L)
alp[0] = dne - 3
h[0] = (dne-2.0)/3.0
spectrum[0,0]=h[q]
spectrum[0,1]=f_h[q]

dne =  derivative(dataExp_spl,q_R,dx=dx)
D_min = dne
f_h[N_qMom-1] = dne*q_R+3.0-dataExp_spl(q_R)
alp[N_qMom-1] = dne - 3
h[N_qMom-1] = (dne-2.0)/3.0
spectrum[N_qMom-1,0]=h[N_qMom-1]
spectrum[N_qMom-1,1]=f_h[N_qMom-1]

# Fitting D_q from D_max,D_min,D(0),D'(0)
D_0 = 3.0 
der_D_0=-derivative(dataExp_spl,0,dx)
del_D = D_max - D_min  
del_Dp= D_0 - D_min  
del_Dm= D_max - D_0
gamma = -der_D_0 * del_D /(2.0*del_Dp*del_Dm)
tanh_gamma_q = (del_Dp-del_Dm)/del_D
function_D = lambda arg : np.tanh(arg)-tanh_gamma_q
q_prime = fsolve(function_D,0)/gamma
print(der_D_0)
print(D_max,D_0,D_min,gamma,q_prime[0])

D_fit = lambda x : D_max - del_D * 0.5 * ( 1.0 + np.tanh(gamma*(x-q_prime) )) 

# Sorting the spectrum
spectrum_sorted=spectrum[np.argsort(spectrum[:,0])]	

# finding the only the positive holder exponents (others are wrong)
h_star=0
for i in range(0,N_qMom):
    if( spectrum_sorted[i,0] > 0.0 ):
        h_star=i
        break

h_arg_size=40
f_h_spl = interp1d(spectrum_sorted[h_star:,0],spectrum_sorted[h_star:,1],kind='cubic')
h_refined=np.linspace(spectrum_sorted[h_star+1,0],spectrum_sorted[N_qMom-2,0],h_arg_size)

dataOut=np.column_stack((qMom,dataExp,D_q,alp,h,f_h))
np.savetxt(save_dir+'exponents_py.dat',dataOut,fmt=('%10.6f','%30.15f','%30.15f','%30.15f','%30.15f','%30.15f') )

dataOut=np.column_stack((spectrum_sorted[h_star:,0],spectrum_sorted[h_star:,1]))
np.savetxt(save_dir+'spectrum_py.dat',dataOut,fmt=('%10.6f','%20.15f') )

