max_index = 240; 
scale = 100; 

for n=0:max_index
filename = sprintf("output%08u.csv", n ); 
data = load(filename); 
figure(1) 
clf
plot( data(:,1), data(:,2), 'ko' ); 
axis( scale*[-1,1,-1,1] ); 
pause(0.05) 
end