close all
clear variables

data=csvread('ntc.csv');
t=data(:,1);
r=data(:,2);

ad=(r./(r+10)).*1024;

plot(ad,t,'o')

p = polyfit(ad, t, 10);

ad2 = 0:1023;
t2 = round(polyval(p, ad2), 1);
hold on, plot(ad2, t2, 'r');

dlmwrite('data.dlm', t2*10, ',');