
for test=0:20
    % Define the image size and where you want the circle
    rows = 100;
    cols = 100;
    noise = mod(test, 7) * 0.1;
    x1 = randi([20, 50]);
    y1 = randi([20, 50]);
    x3 = randi([50, 80]);
    y3 = randi([50, 80]);
    centerx = (x3 + x1) / 2;
    centery = (y3 + y1) / 2;
    deltax = centerx - x1;
    deltay = centery - y1;
    x2 = centerx - deltay;
    y2 = centery + deltax;
    x4 = centerx + deltay;
    y4 = centery - deltax;
    
    mat(1:100,1:100) = 0;
    for xMat=1:cols
        for yMat=1:rows
            totalArea = triArea(xMat, yMat, x1, y1, x2, y2) + triArea(xMat, yMat, x3, y3, x2, y2) + triArea(xMat, yMat, x1, y1, x4, y4) + triArea(xMat, yMat, x3, y3, x4, y4);
            if (totalArea <= triArea(x1, y1, x2, y2, x3, y3) + triArea(x1, y1, x4, y4, x3, y3))
                mat(xMat,yMat)=255;
            else
                mat(xMat,yMat)=0;
            end
        end
    end
    mat1 = imnoise(mat,'salt & pepper', noise);
    mat2 = imnoise(mat,'gaussian', 0.0, noise);
    mat3 = imnoise(mat,'poisson');
    mat4 = imnoise(mat,'speckle', noise);

    for c=1:cols
        for r=1:rows
            if (mat(r,c)==0)
                mat(r,c)=randi([0,127]);
            else
                mat(r,c)=randi([128,255]);
            end
        end
    end
    
    for c=1:cols
        for r=1:rows
            if (mat1(r,c)==0)
                mat1(r,c)=randi([0,127]);
            else
                mat1(r,c)=randi([128,255]);
            end
        end
    end
    
    for c=1:cols
        for r=1:rows
            if (mat2(r,c)==0)
                mat2(r,c)=randi([0,127]);
            else
                mat2(r,c)=randi([128,255]);
            end
        end
    end
    for c=1:cols
        for r=1:rows
            if (mat3(r,c)==0)
                mat3(r,c)=randi([0,127]);
            else
                mat3(r,c)=randi([128,255]);
            end
        end
    end
    for c=1:cols
        for r=1:rows
            if (mat4(r,c)==0)
                mat4(r,c)=randi([0,127]);
            else
                mat4(r,c)=randi([128,255]);
            end
        end
    end
    
    imwrite(mat, ['s' int2str(test * 5 + 0) '.png']);
    dlmwrite(['s' int2str(test * 5 + 0) '.txt'],mat, 'delimiter', ' ');

    imwrite(mat1, ['s' int2str(test * 5 + 1) '.png']);
    dlmwrite(['s' int2str(test * 5 + 1) '.txt'],mat1, 'delimiter', ' ');

    imwrite(mat2, ['s' int2str(test * 5 + 2) '.png']);
    dlmwrite(['s' int2str(test * 5 + 2) '.txt'],mat2, 'delimiter', ' ');

    imwrite(mat3, ['s' int2str(test * 5 + 3) '.png']);
    dlmwrite(['s' int2str(test * 5 + 3) '.txt'],mat3, 'delimiter', ' ');

    imwrite(mat4, ['s' int2str(test * 5 + 4) '.png']);
    dlmwrite(['s' int2str(test * 5 + 4) '.txt'],mat4, 'delimiter', ' ');
end