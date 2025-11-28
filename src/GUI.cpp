#include "GUI.hpp"
#include "GameRule.hpp"

static void getUserInput(string &answer, int &ruleChoice)
{
    cout << "Dimensions ([Largeur]x[Hauteur]): ";
    cin >> answer;
    cout << "\nChoisissez les règles du jeu :" << endl;
    cout << "1 - Classic (Conway)" << endl;
    cout << "2 - Life is Short" << endl;
    cout << "3 - Day and Night" << endl;
    cout << "4 - Wrap Around" << endl;
    cout << "5 - Lonely World" << endl;
    cout << "6 - Seeds" << endl;
    cout << "7 - High Life" << endl;
    cout << "8 - Coral Growth" << endl;
    cout << "9 - Stafford" << endl;
    cout << "0 - Maze" << endl;
    cout << "Choix > ";
    cin >> ruleChoice;
}

static void initializeWindow(const string &answer, int &width, int &height, int &cellSize, int &windowWidth, int &windowHeight, RenderWindow &window)
{
    string path = "input/" + answer + ".txt";
    int maxWindowWidth = 0;
    int maxWindowHeight = 0;
    int cellSizeByWidth = 0;
    int cellSizeByHeight = 0;

    ifstream file(path);
    file >> width >> height;
    file.close();
    VideoMode desktop = VideoMode::getDesktopMode();
    maxWindowWidth = desktop.width * 0.9;
    maxWindowHeight = desktop.height * 0.9;
    cellSizeByWidth = maxWindowWidth / width;
    cellSizeByHeight = maxWindowHeight / height;
    cellSize = min(cellSizeByWidth, cellSizeByHeight);
    if (cellSize < 3)
        cellSize = 3;
    if (cellSize > 20)
        cellSize = 20;
    windowWidth = width * cellSize;
    windowHeight = height * cellSize;
    window.create(VideoMode(windowWidth, windowHeight), "Game of Life", Style::Default);
    window.setFramerateLimit(60);
}

static void setupGrid(Grid &grid, const string &answer, int ruleChoice, int windowWidth, int windowHeight)
{
    string path = "input/" + answer + ".txt";
    grid.initialize(path);
    switch(ruleChoice) {
        case 1:
            grid.setRuleSet(RuleType::CLASSIC);
            break;
        case 2:
            grid.setRuleSet(RuleType::LIFE_IS_SHORT);
            break;
        case 3:
            grid.setRuleSet(RuleType::DAY_AND_NIGHT);
            break;
        case 4:
            grid.setRuleSet(RuleType::WRAPAROUND);
            break;
        case 5:
            grid.setRuleSet(RuleType::LONELY_WORLD);
            break;
        case 6:
            grid.setRuleSet(RuleType::SEEDS);
            break;
        case 7:
            grid.setRuleSet(RuleType::HIGHLIFE);
            break;
        case 8:
            grid.setRuleSet(RuleType::CORAL_GROWTH);
            break;
        case 9:
            grid.setRuleSet(RuleType::STAFFORD);
            break;
        case 0:
            grid.setRuleSet(RuleType::MAZE);
            break;
        default:
            grid.setRuleSet(RuleType::CLASSIC);
    }
    grid.setBackground("assets/background.png", 100.0f);
    grid.updateBackgroundSize(windowWidth, windowHeight);
}

static void setupUI(Grid &grid, Font &font, Text &ruleText)
{
    if (font.loadFromFile("assets/DejaVuSans.ttf")) {
        ruleText.setFont(font);
        ruleText.setCharacterSize(20);
        ruleText.setFillColor(Color::White);
        ruleText.setPosition(10, 10);
        ruleText.setString(grid.getCurrentRuleName());
    }
}

static void handleKeyPress(Keyboard::Key key, Grid &grid, GameRule &rules, bool &paused, Text &ruleText, RenderWindow &window)
{
    if (key == Keyboard::Escape)
        window.close();
    if (key == Keyboard::Space)
        paused = !paused;
    if (key == Keyboard::R)
        rules.randomize();
    if (key == Keyboard::O)
        rules.randomizeWithObstacles();
    if (key == Keyboard::C)
        rules.clear();
    if (key == Keyboard::P)
        rules.spawnRandomPattern();
    if (key == Keyboard::I)
        rules.invertAll();
    if (key == Keyboard::Num1)
        grid.setRuleSet(RuleType::CLASSIC);
    if (key == Keyboard::Num2)
        grid.setRuleSet(RuleType::LIFE_IS_SHORT);
    if (key == Keyboard::Num3)
        grid.setRuleSet(RuleType::DAY_AND_NIGHT);
    if (key == Keyboard::Num4)
        grid.setRuleSet(RuleType::WRAPAROUND);
    if (key == Keyboard::Num5)
        grid.setRuleSet(RuleType::LONELY_WORLD);
    if (key == Keyboard::Num6)
        grid.setRuleSet(RuleType::SEEDS);
    if (key == Keyboard::Num7)
        grid.setRuleSet(RuleType::HIGHLIFE);
    if (key == Keyboard::Num8)
        grid.setRuleSet(RuleType::CORAL_GROWTH);
    if (key == Keyboard::Num9)
        grid.setRuleSet(RuleType::STAFFORD);
    if (key == Keyboard::Num0)
        grid.setRuleSet(RuleType::MAZE);
    ruleText.setString(grid.getCurrentRuleName());
}

static void handleMousePress(Event::MouseButtonEvent &mouseBtn, RenderWindow &window, GameRule &rules, int cellSize, bool &isDragging, Vector2i &lastMousePos)
{
    int x = 0;
    int y = 0;
    Vector2f worldPos;

    if (mouseBtn.button == Mouse::Middle) {
        isDragging = true;
        lastMousePos = Mouse::getPosition(window);
    } else {
        worldPos = window.mapPixelToCoords(Vector2i(mouseBtn.x, mouseBtn.y));
        x = worldPos.x / cellSize;
        y = worldPos.y / cellSize;
        if (mouseBtn.button == Mouse::Left)
            rules.clickCell(x, y);
        if (mouseBtn.button == Mouse::Right)
            rules.explode(x, y, 35);
    }
}

static void handleMouseMove(RenderWindow &window, bool isDragging, View &view, Vector2i &lastMousePos)
{
    Vector2i currentMousePos;
    Vector2i delta;

    if (isDragging) {
        currentMousePos = Mouse::getPosition(window);
        delta = lastMousePos - currentMousePos;
        view.move(delta.x, delta.y);
        window.setView(view);
        lastMousePos = currentMousePos;
    }
}

static void handleMouseWheel(Event::MouseWheelScrollEvent &wheel, float &zoomLevel, int windowWidth, int windowHeight, View &view, RenderWindow &window)
{
    if (wheel.delta > 0)
        zoomLevel *= 0.9f;
    else
        zoomLevel *= 1.1f;
    if (zoomLevel < 0.1f)
        zoomLevel = 0.1f;
    if (zoomLevel > 5.0f)
        zoomLevel = 5.0f;
    view.setSize(windowWidth * zoomLevel, windowHeight * zoomLevel);
    window.setView(view);
}

static void handleResize(Event::SizeEvent &size, View &view, float zoomLevel, int &windowWidth, int &windowHeight, Grid &grid, RenderWindow &window)
{
    FloatRect visibleArea(0, 0, size.width, size.height);
    view = View(visibleArea);
    view.setSize(size.width * zoomLevel, size.height * zoomLevel);
    window.setView(view);
    windowWidth = size.width;
    windowHeight = size.height;
    grid.updateBackgroundSize(windowWidth, windowHeight);
}

static void handleEvents(RenderWindow &window, Grid &grid, GameRule &rules, bool &paused, int cellSize, bool &isDragging, Vector2i &lastMousePos, float &zoomLevel, int &windowWidth, int &windowHeight, View &view, Text &ruleText)
{
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
        if (event.type == Event::KeyPressed)
            handleKeyPress(event.key.code, grid, rules, paused, ruleText, window);
        if (event.type == Event::MouseButtonPressed)
            handleMousePress(event.mouseButton, window, rules, cellSize, isDragging, lastMousePos);
        if (event.type == Event::MouseButtonReleased) {
            if (event.mouseButton.button == Mouse::Middle)
                isDragging = false;
        }
        if (event.type == Event::MouseMoved)
            handleMouseMove(window, isDragging, view, lastMousePos);
        if (event.type == Event::MouseWheelScrolled)
            handleMouseWheel(event.mouseWheelScroll, zoomLevel, windowWidth, windowHeight, view, window);
        if (event.type == Event::Resized)
            handleResize(event.size, view, zoomLevel, windowWidth, windowHeight, grid, window);
    }
}

static void render(RenderWindow &window, Grid &grid, View &view, Font &font, Text &ruleText)
{
    window.clear();
    grid.game(window);
    window.setView(window.getDefaultView());
    if (font.getInfo().family != "")
        window.draw(ruleText);
    window.setView(view);
    sleep(milliseconds(50));
}

void GUI::run()
{
    srand(time(NULL));
    int width = 0;
    int height = 0;
    int cellSize = 0;
    int windowWidth = 0;
    int windowHeight = 0;
    bool paused = false;
    bool isDragging = false;
    float zoomLevel = 1.0f;
    string answer = "";
    int ruleChoice = 0;
    Vector2i lastMousePos;
    Font font;
    Text ruleText;
    getUserInput(answer, ruleChoice);
    RenderWindow window;
    initializeWindow(answer, width, height, cellSize, windowWidth, windowHeight, window);
    Grid grid(width, height, cellSize);
    setupGrid(grid, answer, ruleChoice, windowWidth, windowHeight);
    GameRule rules(&grid);
    View view = window.getDefaultView();
    setupUI(grid, font, ruleText);
    while (window.isOpen()) {
        handleEvents(window, grid, rules, paused, cellSize, isDragging, lastMousePos, zoomLevel, windowWidth, windowHeight, view, ruleText);
        if (!paused)
            grid.update();
        render(window, grid, view, font, ruleText);
    }
}