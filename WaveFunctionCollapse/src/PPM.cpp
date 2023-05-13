#include "../include/PPM.h"

bool PPMPixel::operator==(PPMPixel pix) {
    return (static_cast<unsigned>(pix.red)==static_cast<unsigned>(red)) && (static_cast<unsigned>(pix.green)==static_cast<unsigned>(green)) && (static_cast<unsigned>(pix.blue)==static_cast<unsigned>(blue));
}

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

std::string PPMPixel::toStringBGR() {
    std::string st = "";
    st += '(';
    st += std::to_string(static_cast<unsigned>(blue));
    st += ',';
    st += std::to_string(static_cast<unsigned>(green));
    st += ',';
    st += std::to_string(static_cast<unsigned>(red));
    st += ") ";
    return st;
}

PPMImage::PPMImage(int X, int Y) {
    x = X;
    y = Y;
    data = (PPMPixel*)(malloc(x * y * sizeof(PPMPixel)));
}

PPMImage::PPMImage(const char *filename) {
    std::string mMagic;
    std::ifstream infile(filename, std::ifstream::binary);
    // Examine if the file could be opened successfully
    if (!infile.is_open()) 
    {
        std::cout << "Failed to open " << filename << std::endl;
        exit(1);
    }

    infile >> mMagic;
    infile.seekg(1, infile.cur);
    char c;
    infile.get(c);

    if (c == '#')
    {
        while (c != '\n')
        {
            infile.get(c);
        }
    }
    else
    {
        infile.seekg(-1, infile.cur);
    }

    int rgb_comp_color;
    
    infile >> x >> y >> rgb_comp_color;

    if (rgb_comp_color != 255)
    {
        std::cout << "Failed to read " << filename << std::endl;
        std::cout << "Got PPM maximum value: " << rgb_comp_color << std::endl;
        std::cout << "Maximum pixel has to be 255" << std::endl;
        exit(1);
    }

    uint8_t * mBuffer = new uint8_t[x * y * 3];

    infile.seekg(1, infile.cur);
    infile.read(reinterpret_cast<char *>(mBuffer), x * y * 3);

    //alloc memory form image
    data = (PPMPixel*)(malloc(sizeof(PPMPixel)*x*y));

    for (int i = 0; i < x*y*3; i+=3) {
        PPMPixel* pix = new PPMPixel();
        infile >> mBuffer[i];
        infile >> mBuffer[i+1];
        infile >> mBuffer[i+2];
        pix->red = static_cast<unsigned>(mBuffer[i]);
        pix->green = static_cast<unsigned>(mBuffer[i+1]);
        pix->blue = static_cast<unsigned>(mBuffer[i+2]);
        data[i/3] = *pix;
        //std::cout << pix->toString() << "\n";
        //std::cout << data[i/3].toString() << "\n";
    }
    //fclose(fp);
}

void PPMImage::writePixel(int xcoord, int ycoord, PPMPixel* pix) {
    data[xcoord+ycoord*x] = *pix;
}

PPMPixel PPMImage::pixelAt(int xcoord, int ycoord) {
    PPMPixel pix = data[x*ycoord+xcoord];
    return pix;
}

void PPMImage::operator=(PPMImage img) {
    x = img.x;
    y = img.y;
    data = (PPMPixel*)(malloc(x * y * sizeof(PPMPixel)));
    for (int i = 0; i < img.y; i++) {
        for (int j = 0; j < img.x; j++) {
            PPMPixel pix = img.pixelAt(j,i);
            writePixel(j,i,&(pix));
        }
    }
}

bool PPMImage::operator==(PPMImage img) {
    if (x != img.x || y != img.y) {
        return false;
    }
    else {
        for (int i = 0; i < img.y; i++) {
            for (int j = 0; j < img.x; j++) {
                if (!(img.pixelAt(j,i) == pixelAt(j,i))) {
                    return false;
                }
            }
        }
        return true;
    }
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

void PPMImage::saveImage(const char *filename) {
    std::ofstream fout(filename);
    fout << "P3\n";
    fout << x << " " << y << "\n";
    fout << "255\n";

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            fout << pixelAt(j,i).red << " ";
            fout << pixelAt(j,i).green << " ";
            fout << pixelAt(j,i).blue << "\n";
        }
    }
    fout.close();
}
