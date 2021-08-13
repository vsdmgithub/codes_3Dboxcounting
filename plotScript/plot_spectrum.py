from analysis import *

fig = plt.figure(figsize =(figWidth,figHeight))
ax  = fig.add_axes([0,0,1,1])

for axis in ['top','bottom','left','right']:
    ax.spines[axis].set_linewidth(linW1)
    ax.spines[axis].set_color(colK1)

plt.style.use('seaborn-paper')
rc('font',**{'family':'sans-serif','sans-serif':['DejaVu Sans']})

formatter=ticker.ScalarFormatter(useMathText=True)
formatter.set_scientific(True)
formatter.set_powerlimits((-1,1))
title_pad=-2

ax.plot(h[1:N_qMom-1],D_h[1:N_qMom-1], linewidth=linW2, color=colB2, marker='o',markersize=marS4 )

ax.tick_params(axis='both',which='major',direction='in',colors=colK1,labelsize=fsTk3,length=tkL3,width=tkW2,pad=0.8)
# ax.set_xlabel(r' $\mathsf{ q }$',labelpad=0,color=colK1,fontsize=fsLb3)
# ax.set_ylabel(r' $\mathsf{ \tau_q$',labelpad=0,color=colK1,fontsize=fsLb3)

plt.savefig('spectrum.pdf',dpi=dpi2,transparent=True,bbox_inches='tight')
