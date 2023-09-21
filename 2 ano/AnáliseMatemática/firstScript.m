% Exercício 13.b.iii)

xgraf=linspace(-1,1);
pgraf=polyval(p,xgraf);
qgraf=polyval(q,xgraf);
plot(xgraf,pgraf,xgraf,qgraf);
legend('p','q');