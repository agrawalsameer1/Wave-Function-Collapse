#include "../include/PPM.h"

std::string PPMPixel::toString() {
    std::string st = "";
    st += '(';
    st +=  std::to_string(static_cast<unsigned>(red));
    st += ',';
    st += std::to_string(static_cast<unsigned>(green));
    st += ',';
    st += std::to_string(static_cast<unsigned>(blue));
    st += ") ";
    return st;
}


void PPMImage::readPPM(const char *filename) {
    char buff[16];
    FILE *fp;
    int c, rgb_comp_color;
    
    //open PPM file for reading
    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

    //read image format
    if (!fgets(buff, sizeof(buff), fp)) {
        perror(filename);
        exit(1);
    }

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
        fprintf(stderr, "Invalid image format (must be 'P6')\n");
        exit(1);
    }

    //check for comments
    c = getc(fp);
    while (c == '#') {
        while (getc(fp) != '\n')
        ;
        c = getc(fp);
    }

    ungetc(c, fp);

    //read image size information
    if (fscanf(fp, "%d %d", &x, &y) != 2) {
        fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
        exit(1);
    }   

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
        fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
        exit(1);
    }

    //check rgb component depth
    if (rgb_comp_color!= RGB_COMPONENT_COLOR) {
        fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
        exit(1);
    }

    while (fgetc(fp) != '\n') 
    ;

    //alloc memory form image
    data = (PPMPixel*)malloc(x * y * sizeof(PPMPixel));
    
    //define temp array to hold our pixels
    unsigned char *pixels = new unsigned char[x*y*3];
    
    //transfer pixel data to img
    int i = 0;
    for (unsigned char *ptr = pixels; fscanf(fp, "%c", ptr) != EOF; ptr+=3) {
        PPMPixel* pix = new PPMPixel();
        pix->red = static_cast<unsigned>(*ptr);
        pix->green = static_cast<unsigned>(*(ptr+1));
        pix->blue = static_cast<unsigned>(*(ptr+2));
        data[i] = *pix;
        i++;
    }
    fclose(fp);
}

PPMPixel PPMImage::pixelAt(int xcoord, int ycoord) {
    return *(data + (sizeof(PPMPixel)*(x*ycoord+xcoord)));
}

std::ostream& operator<<(std::ostream& os, PPMImage img) {
    for (int i = 0; i < img.y; i++) {
        for (int j = 0; j < img.x; j++) {
            os << img.pixelAt(j, i).toString();
            os << " ";
        }
        os << "\n";
    }
    return os;
}