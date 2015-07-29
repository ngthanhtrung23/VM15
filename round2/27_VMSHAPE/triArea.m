function s = triArea(x1, y1, x2, y2, x3, y3)
    s = abs((x1 - x2) * (y1 + y2) + (x2 - x3) * (y2 + y3) + (x3 - x1) * (y3 + y1)) * 0.5;
end

