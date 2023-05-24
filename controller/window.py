import pygame
import random
import pygame.freetype

SCREEN_WIDTH = 750
SCREEN_HEIGHT = 200

class Window:
    def __init__(self):
        pygame.init()

        # Set up the display
        self.width, self.height = SCREEN_WIDTH, SCREEN_HEIGHT
        self.screen = pygame.display.set_mode((self.width, self.height))
        pygame.display.set_caption("Fyrryx GUI")

        # Define colors
        self.WHITE = (255, 255, 255)
        self.BLACK = (0, 0, 0)
        self.GRAY = (128, 128, 128)

        # Retro font
        self.font_path = "pixeloid-font/PixeloidMono.ttf"
        self.font_size = 28
        self.font = pygame.freetype.Font(self.font_path, self.font_size)

        # Initialize person information
        self.name = "John Doe"
        self.age = 25
        self.magnetic_field = random.choice(["Up", "None", "Down"])

    def update_info(self, received_data):
        self.name = received_data["Name"]
        self.age = received_data["Age"]
        self.magnetic_field = received_data["MagneticField"]

    def run(self):
        # Game loop
        running = True
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

            # Clear the screen
            self.screen.fill(self.WHITE)

            # Draw table layout
            cell_width = self.width // 2
            cell_height = self.height // 3

            # Draw vertical lines
            pygame.draw.line(self.screen, self.BLACK, (cell_width, 0), (cell_width, self.height), 2)

            # Draw horizontal lines
            pygame.draw.line(self.screen, self.BLACK, (0, cell_height), (self.width, cell_height), 2)
            pygame.draw.line(self.screen, self.BLACK, (0, cell_height * 2), (self.width, cell_height * 2), 2)

            # Render text surfaces
            text_x = 20

            # Center vertically within each cell
            text_y = cell_height // 2 - self.font_size // 2
            self.font.render_to(self.screen, (text_x, text_y), "Name:", self.BLACK)

            # Center vertically within each cell
            text_y += cell_height
            self.font.render_to(self.screen, (text_x, text_y), "Age:", self.BLACK)

            # Center vertically within each cell
            text_y += cell_height
            self.font.render_to(self.screen, (text_x, text_y), "Magnetic Field:", self.BLACK)

            text_x += cell_width

            # Center vertically within each cell
            text_y = cell_height // 2 - self.font_size // 2
            self.font.render_to(self.screen, (text_x, text_y), self.name, self.GRAY)

            # Center vertically within each cell
            text_y += cell_height
            self.font.render_to(self.screen, (text_x, text_y), str(self.age), self.GRAY)

            # Center vertically within each cell
            text_y += cell_height
            self.font.render_to(self.screen, (text_x, text_y), self.magnetic_field, self.GRAY)

            # Update the display
            pygame.display.flip()

        # Quit the game
        pygame.quit()