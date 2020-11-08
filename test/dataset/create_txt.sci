//It seems there is a bug in Scilab when reading 2-bit paletted PNG bas?3p02.png
//Scilab read data and wrongly cast it to boolean, loosing RGB from colormap
//This file has been removed
function create_txt()
    for png_file = ls("*.png")'
        [start,final, match, foundString] = regexp(basename(png_file),"/([0-9][a-z])/");
        select foundString
        case "0g"
            must_be_gray = %T
        case "4a"
            must_be_gray = %T
        else
            must_be_gray = %F
        end
        create_txt_for(png_file, png_file + ".txt", must_be_gray)
    end
endfunction

function create_txt_for(png_file, txt_filename, must_be_gray)
    printf("Create txt file for %s\n", png_file)
    img = imread(png_file);
    depth = size(img,3);
    scale = 1;
    if(must_be_gray && depth >= 3)
        img = img(:,:,3:depth);
        depth = size(img,3);
    end
    if(type(img(1,1,1)) == 4)
        scale = 255;
    end
    fd = mopen(txt_filename, "wt");
    nbRows = size(img,1);
    nbCols = size(img,2);
    for r = 1:nbRows
        for c = 1:nbCols
            for d = 1:depth
                mfprintf(fd, "%d ", uint64(img(r,c,d)) * scale);
            end
        end
    end
    mclose(fd);
endfunction
