'''
PROGRAM TO PLOT THE SECTION OF DISSIPATION FIELD
'''
from packagesPlot import *
from functionsPlot import *
from parametersPlot import *

#-----------------------
# SECTION OF DISSIPATION 
#-----------------------

# Data Variables
N = 512 
intMethod='none'
cmap='afmhot'
cmap='coolwarm'
sec=np.array([[0.0]*N]*N)
file_dir='../data_dissField/DSCODE/'
save_dir='../data_dissField/DSCODE/'

# Reading files
filename='sec_0.dat'
filepath=file_dir+filename

data=np.loadtxt(filepath)
k=0
for i in range(0,N):
    for j in range(0,N):
        sec[i,j]=data[i*N+j]

sec = np.log(sec)
cbMin = np.amin(sec)
cbMax = np.amax(sec)

# Plotting
plt.rcParams["font.family"] = "sans-serif"
plt.rcParams["font.sans-serif"]="DejaVu Sans"
plt.rcParams.update({
  "pgf.texsystem": "pdflatex",
  "pgf.preamble": "\n".join([
    r"\usepackage[utf8x]{inputenc}",
    r"\usepackage[T1]{fontenc}",
    r"\usepackage{cmbright}",
    r"\usepackage{amsfonts}",
    r"\usepackage{amsmath}",
    r"\usepackage{amssymb}",
    r"\usepackage[helvet]{sfmath}"
    ]),
    })

fig      =   plt.figure(figsize=(2,2))
ax       =   fig.add_axes([0.01,0.01,0.8,0.8])

rc('font',**{'family':'sans-serif','sans-serif':['DejaVu Sans']})

plt.style.use('seaborn-dark')

for axis in ['top','bottom','left','right']:
    ax.spines[axis].set_linewidth(linW0)
    ax.spines[axis].set_color(colK1)

im=ax.matshow(sec,interpolation=intMethod, extent=[0, N, 0, N], origin='lower',cmap=cmap,vmin=cbMin,vmax=cbMax)

axC=fig.add_axes([.82,0.1,0.03,0.8])
axC.tick_params(which='major',direction='in',labelsize=0.85*fsTk2,length=tkL2,color=colK1,width=tkW2,pad=0.8)
axC.tick_params(which='minor',length=0)
cbar=fig.colorbar(im,cax=axC)
# cbar=fig.colorbar(im,cax=axC,ticks=ticker.MultipleLocator(5))
cbar.outline.set_linewidth(linW0)

for tick in cbar.ax.get_yticklabels():
    tick.set_fontname("DejaVu Sans")

ax.tick_params(axis='both',which='major',direction='in',colors=colK1,labelsize=0.8*fsTk2,length=tkL2,width=tkW2,pad=0.8)

ax.set_xlabel(r'$\mathsf{y}$',color=colK1,fontsize=fsLb2,labelpad=-2)
ax.set_ylabel(r'$\mathsf{x}$',color=colK1,fontsize=fsLb2,labelpad=-2)

plt.savefig(save_dir+'plot_sec_DSCODE_z_{}.pdf'.format(k),dpi=dpi2,transparent=True,bbox_inches='tight')

