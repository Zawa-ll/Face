#include <opencv2/opencv.hpp>

using namespace std;
int main()
{
}

// Method for showing an image
int show_img()
{
    cv::Mat img = cv::imread("data/cat.png", -1);

    if (img.empty())
        return -1;

    cv::namedWindow("cat", cv::WINDOW_AUTOSIZE);
    cv::imshow("cat", img);
    cv::waitKey(0); // remain open when set to 0
    cv::destroyWindow("cat");

    return 0;
}

// Method for showing a video
int show_video()
{
    cv::VideoCapture cap;
    cv::namedWindow("video", cv::WINDOW_AUTOSIZE);
    cap.open("tools/test.avi");
    cv::Mat frame; // fram for receiving every byte of image

    for (;;)
    {
        cap >> frame; // input bits from video till no bit left
        if (frame.empty())
            break;

        cv::imshow("video", frame);

        char c = (char)cv::waitKey(200);

        if (c == 27) // ESC on Keyboard: ascii = 27
            break;
    }
    return 0;
}

int camera()
{
    int camera_id = 0;
    cv::VideoCapture cap;
    cap.open(canera_id);
    cv::Mat frame;

    bool is_face = false;

    cv::CascadeClassifier face_model;
    if (is_face)
    {
        char *face_model_path = "tools/haarcascade_frontalface_alt.xml"; // Face Model provide by OpenCV
        if (!face_model.load(face_model_path))
        {
            return -1; // fail to read frontalface model
        }
    }

    for (;;)
    {
        cap >> frame;
        if (frame.empty()) // Camera captures nothing: first bit capture is empty
            break;

        if (is_face)
        {
            // TODO:
            vector<cv::Rect> faces; // pixels for frontal face, vector for multiple faces
            face_model.detectMultiScale(frame,
                                        faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE,
                                        cv::Size(30, 30));

            for (int i = 0; i < faces.size(); i++)
            {
                cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2); // Get the center of faces[i]
                ellipse(fame, center, cv::Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, cv : Scalar(255, 0, 255), 4, 8, 0);
            }

            cv::imshow("video", frmae);
        }

        cv::imshow("video", frame);

        char c = (char)cv::waitKey(10);

        if (c == 27) // ESC on Keyboard: ascii = 27
            break;
    }

    return 0;
}

int rec_camera()
{
    int camera_id = 0;
    cv::VideoCapture cap;
    cap.open(camera_id);
    cv::Mat frame;

    cv::VideoWriter output_video;

    int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    output_video.open("%d:/rec.avi", CV_FOURCC("M", "J", "P", "G", 30.0, cv::Size(width, height)));

    for (;;)
    {
        cap >> frame;
        if (frame.empty())
            break;

        cv::imshow("video", frame); // Output one bit of video each time

        output_video.write(frame);

        char c = (char)cv::waitKey(10) // Waiting for Key from keyboard every 10 ms

            if (c == 27) break;
    }

    return 0;
}

int slider()
{
    cv::namedWindow("slider", cv::WINDOW_AUTOSIZE);

    g_cap.open(string("data/test.avi");)

        int frames = (int)g_cap.get(VC_CAP_PROP_FRAME_COUNT);
    int tmpw = (int)g_cap.get(CV_CAP_PROP_FRMAE_WIDTH);
    int tmph = (int)g_cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    cout << "Video has " << frames << " frmaes of dimensions of (" << tmpw << ", " << tmph << ")." << endl;

    cv::createTrackbar(
        "Position",
        "slider",
        &g_slider_position,
        frames,
        onTrackbarSlide);

    cv::Mat frame;

    for (;;)
    {
        if (g_run != 0)
        {
            g_cap >> frame;
            if (frame.empty())
                break;
            int current_pos = (int)g_cap.get(CV_CAP_PROP_POS_FRAMES);
            g_dontset = 1;

            cv::setTrackbarPos("Position", "slider", current_pos);
            cv::imshow("slider", frame);
            g_run -= 1;
        }

        char c = (char)cv::waitKey(10);

        if (c == 's')
        { // single step mode
            g_run = 1;
            cout << "Single step, run = " << g_run << endl;
        }

        if (c == 'r')
        {
            g_run = -1;
            cout << "Run mode, run = " << g_run << endl;
        }

        if (c == 27)
            break;
    }
}

int pixels()
{
    cv::Mat img_rb, img_gry, img_cny, img_pyr, img_pyr2;

    cv::namedWindow("Gray", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Canny", cv::WINDOW_AUTOSIZE);

    img_rgb = cv::imread("data/cat.png");

    // Convert color img to gray img
    cv::cvtColor(img_rgb, img_gry, cv::COLOR_BGR2GRAY);

    cv::pyrDown(img_gry, img_pyr); // downsize the img
    cv::pyrDown(img_pyr, img_pyr2);

    // Fetch the boarder of a img
    cv::Canny(img_pyr2, img_cny, 10, 100, 3, true);

    int x = 16, y = 32;
    cv::Vec3b intensity = img_rgb.at<cv::Vec3b>(y, x); // Fetch pixel in mode of Vec3b (3 val in color pixel)

    uchar blue = intensity[0];
    uchar green = intensity[1];
    uchar red = intensity[2];

    cout << "At (x, y) = (" << x << "," << y << "): (b,g,r) = (" << (unsigned int)blue << "," << (unsigned int)green << "," << (unsigned int)red << ")" << end;

    cout << "Gray pixel there is: " << (unsigned int)img_gry.at<uchar>(y, x) << endl; // Fetch pixel in mode of uchar (only 1 val in gray pixel)

    x /= 4;
    y /= 4;

    cout << "Pyramid2 pixel there is" << (unsigned int)img_pyr2.at<uchar>(y, x) << endl;

    img_cny.at<uchat>(x, y) = 128; // Set the Canny pixel in the value of 128

    cv::imshow("Gray", img_gry);
    cv::imshow("Canny", img_cny);

    cv::waitKey(0);

    return 0;
}

int read_video()
{
    cv::nameWindow("video", cv::WINDOW_AUTOSIZE); // Window for displaying video bits

    cv::VideoCapture cap;

    if (!cap.open("data/test.avi"))
    {
        cerr << "Cannot Open Video File" << endl;
        return -1;
    }

    cv::Point pt1(100, 100), pt2(300, 300); // st and ed for the string to be added

    int max_buffer; // Maximum Buffer Size

    cv::Mat rawImage;

    // Output File Streams For Storing Data in b,g,r channels, respectively
    ofstream b, g, r;
    b.open("blines.csv");
    g.open("glines.csv");
    r.open("rlines.csv");

    for (;;)
    {
        cap >> rawImage;
        if (!rawImage.data)
            break;

        cv::LineIterator it(rawImage, pt1, pt2, 8); // Iterator for iterating through each pixel on the string

        for (int j = 0; j < it.count; ++j, ++it)
        {
            b << (int)(*it)[0] << ",";
            g << (int)(*it)[1] << ",";
            r << (int)(*it)[2] << ",";

            (*it)[2] = 255; // Red channel value set to 255
        }

        cv::imshow("video", rawImage);

        int c = cv::waitKey(1000);

        b << "\n";
        g << "\n";
        r << "\n";
    }

    b << endl;
    g << endl;
    r << endl;
    b.close();
    g.close();
    r.close();

    cout << "\nData has been store in file: blines.csv, glines.csv, and rlines.csv\n"
}

void on_trackbar(int, void *)
{
    cv::threshold(g_gray, g_binary, g_thresh, 255, cv::THRESH_BINARY); // g_thresh used for convertting into binary value, for controlling result in binary form
    vector<vector<cv::Point>> contours;
    cv::findContours(
        g_binary,
        contours,
        cv::noArray(),
        cv::RETR_LIST,
        cv::CHAIN_APPROX_SIMPLE);

    // draw contours on g_binary
    g_binary = cv::Scalar::all(0);
    cv::drawContours(g_binary, contours, -1, cv::Scalar::all(255));

    cv::imshow("Contours", g_binary);
}

int find_contours()
{
    if (g_gray = cv::imread("data/fruits.jpg", 0).empty())
    {
        cout << "Fail to Read Image \n"
             << endl;

        return -1;
    }

    cv::namedWindow("Contours", 1);

    cv::createTrackbar( // trackbar in "contours" window
        "Threshold",
        "Contours",
        &g_thresh,
        255,
        on_trackbar // callback function
    );
    on_trackbar(0, 0); // Initialize the Display

    cv::waitKey(); // Wait for key press

    return 0;
}

int draw_contours()
{
    cv::Mat img, img_edge, img_color;
    img = cv : imread("data/cat.png", cv::IMREAD_GRAYSCALE);
    if (img.empty())
    {
        cout << "Fail to dead in file \n"
             << endl;
        return -1;
    }

    // Thresholding image to Binary, pixel greater than 128 will be 255, lower than 128 will be 0
    cv::threshold(img, img_edge, 128, 255, cv::THRESH_BINARY);

    cv::imshow("Image after Thresholding to Binary", img_edge);

    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;

    cv::findContours( // Find Contour in Image
        img_edge,
        contours,
        hierarchy,
        cv::RETR_LIST,
        cv::CHAIN_APPROX_SIMPLE);

    cout << "\n\n Press any key to draw the next contour, press ESC to exit \n\n";
    cout << "Total Number of Contour Detected: " << countours.size() << endl;

    vector<int> sortIdx(contours.size());
    vector<float> areas(contours.size());

    for (int n = 0; n < (int)contours.size(); n++)
    {
        sortIdx[n] = n;
        areas[n] = contourArea(contours[n], false); // Get Area of Each Contour
    }

    sort(sortIdx.begin(), sortIdx.end(), AreaCmp(areas));

    for (int n = 0; n < (int)sortIdx.size(); n++)
    {
        int idx = sortIdx[n];

        // Conver Gray Image into Colored Image, For Drawing Contour
        cv::cvtColor(img, img_color, cv::COLOR_GRAY2BGR);

        // Drawing Contour requires coloured info
        cv::drawContours(
            img_color, contours, idx,
            cv::Scalar(0, 0, 255), 2, 8, hierarchy,
            0);

        cout << "Contour #" << idx << ": Area = " << areas[idx] << ", Number of vertices = " << contours[idx].size() << endl;

        cv::imshow("Image with Contour Drawn", img_color);

        int k;
        if ((k = cv::waitKey() & 255) == 27)
            break;
    }

    cout << "Finish Drawing All Contours" return 0;
}

int draw_components()
{
    cv::Mat img, img_edge, labels, centroids, img_color, stats;

    img = cv::imread("data/cat.png", cv::IMREAD_GRAYSCALE);
    cv::imshow("raw", img);

    cv::threshold(img, img_edge, 128, 255, cv::THRESH_BINARY);

    cv::imshow("Image After Thresholding to Binary", img_edge);

    int i, nccomps = cv::connectedComponentsWithStats( // Finding Connected Component
               img_edge,
               labels,
               stats,
               centroids);

    cout << "Total Number of Connected Component is: " << nccomps << endl;

    // Color Vector distribute different colors for each component
    vector<cv::Vec3b> colors(nccomps + 1);

    colors[0] = cv::Ve3b(0, 0, 0); // (0, 0, 0) is black color

    // Creating an Color Component same size as IMG, in black color
    img_color = cv::Mat::zeros(img.size(), CV_8UC3);

    // Iterate through each pixel of IMG and
    // Assign color of accompanying Connect Component to img_color
    for (int y = 0; y < img_color.rows; y++)
    {
        for (int x = 0; x < img_color.cols; x++)
        {
            int label = labels.at<int>(y, x);
            CV_Assert(0 <= label && label <= nccomps);
            img_color.at<cv::Vec3b>(y, x) = colors[label];
        }
    }

    cv::imshow("Image with Tag", img_color);

    cv::waitKey();

    return 0;
}

// Measuring the shape difference between two contours by shape context distance
int shape_distance()
{
    Ptr<ShapeContextDistanceExtratctor> mysc = createShapeContextDist

        Mat img1 = imread("shape_sample/3.png", IMREAD_GRAYSCALE);
    Mat img2 = imread("shape_sample/4.png", IMREAD_GRAYSCALE);

    vector<Point> c1 = sampleContour(img1);
    vector<Point> c2 = sampleContour(img2);

    float dis = mysc->computeDistance(c1, c2);

    cout << "Difference(Distance) between the two image is " << dis << endl;

    cv::imshow("SHAPE #1", img1);
    cv::imshow("SHAPE #2", img2);

    cv::waitKey();
}

int fit_line()
{
    cv::Mat img(500, 500, CV_8UC3);

    // Random number generator with seed set to -1
    cv::RNG rng(-1);

    // Loop randomly generated points for straight line fitting
    for (;;)
    {
        chat key;

        int i;
        int count = rng.uniform(0, 100) + 3;
        int outliers = count / 5; // For Calculate number of outliers, should be 1/5 of point's total number

        float a = (float)rng.uniform(0., 200.);
        float b = (float)rng.uniform(0., 40.);
        float angle = (float)rng.uniform(0., CV_PI);
        float cos_a = cos(angle, sin_a = sin(angle));

        cv::Point pt1, pt2;
        vector<cv::Point> poins(count); // Points being generated
        cv::Vec4f line;                 // Attribute for the generated line fitting
        float d, t;

        b = min(a * 0.3f, b);
    }

    // Geerating points close to the line
    for (int i = 0; i < count - outliers; i++)
    {
        float x = (float)rng.uniform(-1. 1.) * a;
        float y = (float)rng.uniform(-1. 1.) * b;

        // Move the generated coordinate points to the center of the image through rotational translation
        points[i].x = cvRound(x * cos_a - y * sin_a + img.cols / 2);
        points[i].x = cvRound(x * sin_a - y * cos_a + img.cols / 2);
    }

    for (; i < count; i++)
    {
        points[i].x = rng.uniform(0, img.cols);
        points[i].y = rng.uniform(0, img.rows);
    }

    cv::fitline(points, line, cv::DIST_L1, 1, 0.001, 0.001);

    // Drawing all points
    img = cv::Scalar::all(0);
    for (int i = 0; i < count; i++)
    {
        cv::circle(img, points[i], 2,
                   i < count - outliers ? cv::Scalar(0, 0, 255)
                                        : cv::Scalar(0, 255, 255),
                   cv::FILLED, CV_AA, 0);

        d = sqrt((double)line[0] * line[0] + (double)Line[1] * line[1]);
        line[0] /= d;
        line[1] /= d;

        t = (float)(img.cols + img.rows);

        pt1.x = cvRound(line[2] - line[0] * t);
        pt1.y = cvRound(line[3] - line[1] * t);
        pt2.y = cvRound(line[2] + line[0] * t);
        pt2.y = cvRound(line[3] + line[1] * t);

        cv::line(img, pt1, pt2, cv::Scalar(0, 255, 0), 3, CV_AA, 0);
        cv::imshow("Fit Line", img);
        key = (char)cv::waitKey(0);

        if (key == 27 || key == 'q' || key == 'Q')
            break;
    }

    return 0;
}