from analysis import *

fig = plt.figure(figsize =(figWidth,figHeight))
ax  = fig.add_axes([0,0,1,1])

for axis in ['top','bottom','left','right']:
    ax.spines[axis].set_linewidth(linW1)
    ax.spines[axis].set_color(colK1)

plt.style.use('seaborn-paper')
rc('font',**{'family':'sans-serif','sans-serif':['DejaVu Sans']})

ax.grid(True,linewidth=linW0,alpha=al2)

formatter=ticker.ScalarFormatter(useMathText=True)
formatter.set_scientific(True)
formatter.set_powerlimits((-1,1))
title_pad=-2

ax.plot(spectrum_sorted[h_star:,0],spectrum_sorted[h_star:,1], linewidth=linW1, color=colR2, marker='o',markersize=1.5*marS4 )
ax.plot(h_refined,f_h_spl(h_refined), linewidth=linW2, color=colR3)
#ax.plot(0.333,3.0,'rx',markersize=3*marS4,alpha=0.8)

ax.tick_params(axis='both',which='major',direction='in',colors=colK1,labelsize=fsTk2,length=tkL2,width=tkW2,pad=0.8)
ax.set_xlabel(r' $\mathsf{ h }$',labelpad=0,color=colK1,fontsize=fsLb3)
ax.set_ylabel(r' $\mathsf{ D(h)}$',labelpad=0,color=colK1,fontsize=fsLb3,rotation=0)
#ax.xaxis.set_major_locator(MultipleLocator(0.2))
#ax.yaxis.set_major_locator(MultipleLocator(0.5))

plt.savefig(save_dir+'spectrum.pdf',dpi=dpi2,transparent=True,bbox_inches='tight')
