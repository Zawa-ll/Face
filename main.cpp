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
