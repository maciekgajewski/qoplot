clf
# create sombrero
x = linspace(-8,8,72);
y = linspace(-8,8,74);
[xx,yy] = meshgrid(x,y);
r = sqrt(xx.^2 + yy.^2) + eps;
zz = sin (r) ./ r;

pcolor(xx,yy,zz);
colormap(jet);
h=get(gca,'Children');
shading interp;
ht=text(2,7,'FaceAlpha = 0.00');
set(ht,'FontSize',12);
for i=0:0.01:1.0
  set(h,'FaceAlpha',i);
  pause(0.02)
  msg=sprintf('FaceAlpha = %4.2f',i);
  set(ht,'String',msg);
end
disp('end of demonstration')
