# About dataset files

## PNG files

`bas*.png` and `z0*.png` files are from [The "official" test-suite for PNG](http://www.schaik.com/pngsuite2011/pngsuite.html).

## JPG files

Since decoding jpeg files is prone to compiler subjectivity, it may appear some errors of plus or minus 1 in color components values between different software. To avoid this, BMP files are provided. They are decompressed versions of JPEG ones using `djpeg` provided by libjpeg library.

When libjpeg version changes, decompressing algorithm may change. So, you'll need to upgrade this BMP files by running `djpeg` one more time.

## TXT files

For reading tests, `testProg` compares read from each image file data with simple ASCII raw data in corresponding *.txt file. These txt files are generated using stored in create_txt.sci scilab script. To avoid using scilab at build time, these txt files are versionned in git repository.

If you want to generate these txt files, download scilab at [scilab.org](https://www.scilab.org). Then, in Scilab GUI, browse to `test` directory and type:

``` scilab
exec('create_txt.sci', -1)
create_txt
```

Or if you want to do it in a shell (of course, you have to deal with PATH and working directory):

``` sh
scilab -e "exec('./create_txt.sci', -1); create_txt;" -nwni -quit
```
