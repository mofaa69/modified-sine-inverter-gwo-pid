
clc; clear; close all;
model_adi = 'inverter_Kopya';  
max_iterasyon = 10;     
kurt_sayisi = 30;       
simulasyon_suresi = 0.3; 

% ARANACAK DEĞERLER [Kp, Ki] 
lb = [0, 0];     
ub = [1, 2];    

dim = 2;

Alpha_pos = zeros(1, dim); Alpha_score = inf; 
Beta_pos = zeros(1, dim);  Beta_score = inf;  
Delta_pos = zeros(1, dim); Delta_score = inf; 

Positions = rand(kurt_sayisi, dim) .* (ub - lb) + lb;
Convergence_curve = zeros(1, max_iterasyon);

fprintf('PI Optimizasyonu Başlıyor... (Trafosuz Sistem)\n');
fprintf('Lütfen Simulink Referans voltajının 12V olduğundan emin ol!\n');

for l = 1:max_iterasyon
    for i = 1:kurt_sayisi
        
        Positions(i,:) = max(Positions(i,:), lb);
        Positions(i,:) = min(Positions(i,:), ub);
        
        Kp = Positions(i, 1);
        Ki = Positions(i, 2);
        Kd = 0; 
        
        assignin('base', 'Kp', Kp);
        assignin('base', 'Ki', Ki);
        assignin('base', 'Kd', Kd);
        
        try
            simOut = sim(model_adi, 'StopTime', num2str(simulasyon_suresi), 'SrcWorkspace', 'current');
            
            if isprop(simOut, 'hata_verisi')
                ham_veri = simOut.hata_verisi;
                veri_uzunlugu = length(ham_veri);
                baslangic_indeksi = floor(veri_uzunlugu * 0.5); 
                temiz_veri = ham_veri(baslangic_indeksi:end);
                fitness = sqrt(mean(temiz_veri.^2));
            else
                fitness = inf;
            end
        catch
            fitness = inf;
        end
        
        % Liderleri Güncelle
        if fitness < Alpha_score
            Alpha_score = fitness; Alpha_pos = Positions(i,:);
            fprintf('>> [%d] YENİ REKOR! Hata: %.4f | [Kp: %.4f, Ki: %.4f]\n', l, Alpha_score, Alpha_pos(1), Alpha_pos(2));
        elseif fitness < Beta_score
            Beta_score = fitness; Beta_pos = Positions(i,:);
        elseif fitness < Delta_score
            Delta_score = fitness; Delta_pos = Positions(i,:);
        end
    end
    
    % Kurt Konumlarını Güncelle
    a = 2 - l * ((2) / max_iterasyon); 
    for i = 1:kurt_sayisi
        for j = 1:dim
            r1 = rand(); r2 = rand();
            A1 = 2 * a * r1 - a; C1 = 2 * r2;
            D_alpha = abs(C1 * Alpha_pos(j) - Positions(i,j));
            X1 = Alpha_pos(j) - A1 * D_alpha;
            
            r1 = rand(); r2 = rand();
            A2 = 2 * a * r1 - a; C2 = 2 * r2;
            D_beta = abs(C2 * Beta_pos(j) - Positions(i,j));
            X2 = Beta_pos(j) - A2 * D_beta;
            
            r1 = rand(); r2 = rand();
            A3 = 2 * a * r1 - a; C3 = 2 * r2;
            D_delta = abs(C3 * Delta_pos(j) - Positions(i,j));
            X3 = Delta_pos(j) - A3 * D_delta;
            
            Positions(i,j) = (X1 + X2 + X3) / 3;
        end
    end
    Convergence_curve(l) = Alpha_score;
    fprintf('İterasyon %d bitti. En iyi hata: %.4f\n', l, Alpha_score);
end

fprintf('\n--- SONUÇLAR ---\n');
fprintf('Kp: %.5f\n', Alpha_pos(1));
fprintf('Ki: %.5f\n', Alpha_pos(2));
assignin('base', 'Kp', Alpha_pos(1));
assignin('base', 'Ki', Alpha_pos(2));
assignin('base', 'Kd', 0);

figure; plot(Convergence_curve); title('PI Optimizasyon Grafiği');