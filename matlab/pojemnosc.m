%wartosci pojemnosci wzorcowych [ohm], zmierzonych za pomoca Agilent E4980A

clear all;
R_wz = [ 104.9, 130.65, 140.61, 147.13, 160.3, 162.32, 179.145, 199.97, 228.27];


addpath('D:\Studia wszystko\Studia 5\sem 3\praca magisterska\pomiary\Pojemnosc');

liczba_rezystorow = 9;
%pobranie danych z mk
%format: rezystancja

Metody = zeros(1024,liczba_rezystorow);
C105; Metody(:,1) = Metoda_1;
C130; Metody(:,2) = Metoda_1;
C140; Metody(:,3) = Metoda_1;
C147; Metody(:,4) = Metoda_1;
C160; Metody(:,5) = Metoda_1;
C162; Metody(:,6) = Metoda_1;
C180; Metody(:,7) = Metoda_1;
C200; Metody(:,8) = Metoda_1;
C230; Metody(:,9) = Metoda_1;


%histogramy pomiarow
figure
for i=1:liczba_rezystorow
    r_max(i)  = max(Metody(:,i));
    r_min(i)  = min(Metody(:,i));
    r_mean(i) = (min(Metody(:,i)) + max(Metody(:,i)))./2;
    r_average(i)  = mean(Metody(:,i));
    subplot(5,2,i);
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
xlabel('wartoœci wzorcowe [pF]')
ylabel('wartoœci zmierzone [pF]')

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
xlabel('Pojemnosc wzorcowa [pF]')
ylabel('Blad wzgledny [%]')


