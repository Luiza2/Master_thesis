%wartosci rezystancji wzorcowych [ohm], zmierzonych za pomoca Agilent
%34401A
clear all;
R_wz = [ 942.25, 975.54, 988.65, 1000.8, 1039.8, 1069.2, 1100.1, 1159.8, 1200, 1230.9, 1250, 1300.4];


addpath('D:\Studia wszystko\Studia 5\sem 3\praca magisterska\pomiary\Metoda4');

liczba_rezystorow = 12;
%pobranie danych z mk
%format: rezystancja

Metody = zeros(1024,liczba_rezystorow);
R950;  Metody(:,1)  = Metoda_4;
R976;  Metody(:,2)  = Metoda_4;
R988;  Metody(:,3)  = Metoda_4;
R1000; Metody(:,4)  = Metoda_4;
R1040; Metody(:,5)  = Metoda_4;
R1070; Metody(:,6)  = Metoda_4;
R1100; Metody(:,7)  = Metoda_4;
R1160; Metody(:,8)  = Metoda_4;
R1200; Metody(:,9)  = Metoda_4;
R1230; Metody(:,10) = Metoda_4;
R1250; Metody(:,11) = Metoda_4;
R1300; Metody(:,12) = Metoda_4;


%histogramy pomiarow
figure
for i=1:liczba_rezystorow
    r_max(i)  = max(Metody(:,i));
    r_min(i)  = min(Metody(:,i));
    r_mean(i) = (min(Metody(:,i)) + max(Metody(:,i)))./2;
    r_average(i)  = mean(Metody(:,i));
    subplot(7,2,i);
    hist(Metody(:,i),40)
    grid on;
end

%wykres wartosci zmierzonych rezystancji w funkcji rezystancji wzorcowych
figure 
for i=1:liczba_rezystorow
    x = [R_wz(i), R_wz(i)];
    y = [r_min(i),r_max(i)];
    plot(x, y, 'r-*')
    hold on;
    plot(R_wz,r_mean,'b--o')
    grid on;
end
plot(R_wz, R_wz, 'r')
xlabel('wartoœci wzorcowe [ohm]')
ylabel('wartoœci zmierzone [ohm]')

%obliczenie bledow wzglednych [%]
blad = zeros(1024,liczba_rezystorow);
x_err = zeros(1024,liczba_rezystorow);
x_average = zeros(liczba_rezystorow,1);
x_err_min = zeros(liczba_rezystorow,1);
x_err_max = zeros(liczba_rezystorow,1);
for j=1:liczba_rezystorow
    for i=1:1024
       blad(i,j) = (Metody(i,j)-R_wz(j))/R_wz(j)*100;%wynik w %
       x_err(i,j) = R_wz(j);
    end
    x_average(j) = (min(blad(:,j))+max(blad(:,j)))./2;
    x_err_min(j) = min(blad(:,j));
    x_err_max(j) = max(blad(:,j));
end

figure
hold on;
plot(x_err, blad(:,:), 'r')
plot(R_wz, x_average, 'r*')
plot(R_wz, x_average, 'b-')
plot(x_err, x_err_min(:,:), 'r*')
plot(x_err, x_err_max(:,:), 'r*')
grid on;
xlabel('Rezystancja wzorcowa [ohm]')
ylabel('Blad wzgledny [%]')


