clf
# create sombrero
x = linspace(-8,8,42);
y = linspace(-8,8,44);
[xx,yy] = meshgrid(x,y);
r = sqrt(xx.^2 + yy.^2) + eps;
zz = sin (r) ./ r;
colormap(jet);
subplot(2,2,1)
pcolor(xx,yy,zz);
shading interp;
h=get(gca,'Children');
set(h,'FaceAlpha',1/3);
title('pcolor plot with alpha=1/3')
subplot(2,2,2)
pcolor(xx,yy,zz);
shading interp
h=get(gca,'Children');
set(h,'FaceAlpha',1/2);
title('pcolor plot with alpha=1/2')
subplot(2,2,3)
pcolor(xx,yy,zz);
shading interp;
h=get(gca,'Children');
set(h,'FaceAlpha',2/3);
title('pcolor plot with alpha=2/3')
subplot(2,2,4);
pcolor(xx,yy,zz);
shading interp
title('pcolor plot with alpha=1.0')
