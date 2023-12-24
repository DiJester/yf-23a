dofile('./data.lua')
print('----yf23a data ---')
print("Mach;Cx0;Cya;B;B4;Omxmax;Aldop;Cymax")
for i = 1, #yf23a_table_data do
    print(string.format("%f;%f;%f;%f;%f;%f;%f;%f", yf23a_table_data[i][1], yf23a_table_data[i][2], yf23a_table_data[i]
        [3],
        yf23a_table_data[i][4], yf23a_table_data[i][5], yf23a_table_data[i][6], yf23a_table_data[i][7],
        yf23a_table_data[i]
        [8]))
end
