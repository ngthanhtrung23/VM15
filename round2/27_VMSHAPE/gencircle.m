for test=0:20
    % Define the image size and where you want the circle
    rows = 100;
    cols = 100;
    radius = randi([10, 50]);
    noise = mod(test, 7) * 0.1;
    center = [randi([radius, 100-radius]), randi([radius, 100-radius])];

    [xMat,yMat] = meshgrid(1:cols,1:rows);
    distFromCenter = sqrt((xMat-center(1)).^2 + (yMat-center(2)).^2);

    mat = im2uint8(distFromCenter<=radius);
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
    
    imwrite(mat, ['c' int2str(test * 5 + 0) '.png']);
    dlmwrite(['c' int2str(test * 5 + 0) '.txt'],mat, 'delimiter', ' ');

    imwrite(mat1, ['c' int2str(test * 5 + 1) '.png']);
    dlmwrite(['c' int2str(test * 5 + 1) '.txt'],mat1, 'delimiter', ' ');

    imwrite(mat2, ['c' int2str(test * 5 + 2) '.png']);
    dlmwrite(['c' int2str(test * 5 + 2) '.txt'],mat2, 'delimiter', ' ');

    imwrite(mat3, ['c' int2str(test * 5 + 3) '.png']);
    dlmwrite(['c' int2str(test * 5 + 3) '.txt'],mat3, 'delimiter', ' ');

    imwrite(mat4, ['c' int2str(test * 5 + 4) '.png']);
    dlmwrite(['c' int2str(test * 5 + 4) '.txt'],mat4, 'delimiter', ' ');
end