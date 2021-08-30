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

for q in range(0,N_qMom):
    ax.plot(dataR[:],dataMom[:,q], linewidth=linW2, marker= markersList[q%10],markersize=marS4,label='q={:3.2f}'.format(qMom[q]) )

ax.tick_params(axis='both',which='major',direction='in',colors=colK1,labelsize=fsTk3,length=tkL3,width=tkW2,pad=0.8)
# ax.set_xlabel(r' $\mathsf{ q }$',labelpad=0,color=colK1,fontsize=fsLb3)
# ax.set_ylabel(r' $\mathsf{ \tau_q$',labelpad=0,color=colK1,fontsize=fsLb3)
# ax.legend()
# h_legend = ax.legend(bbox_to_anchor=(0.01,0.98),ncol=2,loc=2,frameon=False,fontsize=fsLg2,markerscale=1.25,facecolor='none',columnspacing=0.4,borderpad=1.0)
plt.savefig(save_dir+'moments.pdf',dpi=dpi2,transparent=True,bbox_inches='tight')
