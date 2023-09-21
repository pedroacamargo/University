function T=Ex14(n,d,c)

% EX14 Gera uma matriz tridiagonal
% T=TRIDIMENSIONAL(n,d,c)
%   Gera uma matriz tridiagonal T de ordem n que tem o valor d na diagonal principal e o valor c na sub e sobre diagonal
%   PARÂMETROS DE ENTRADA:
%       n: ordem da matriz a gerar.
%       d: real correspondente ao valor da diagonal principal.
%       c: real correspodente ao valor da sobre e sub diagonal.
%
%   PARÂMETRO DE SAÍDA:
%   T: matriz de ordem n que tem o valor d na diagonal principal

if (length(n)~=1) | (fix(n)~=n) | (n < 1)
    error('n has to be a positive integer!')
end

dd=d*ones(1,n);
sd=c*ones(1,n-1);
T=diag(dd)+diag(sd,1)+diag(sd,-1);

end