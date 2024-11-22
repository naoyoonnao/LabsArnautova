import tkinter as tk
from tkinter import ttk
import time
import random
import threading

class Plant:
    def __init__(self, name, water_loss_time, growth_time, fruit_name):
        self.name = name
        self.water_level = 100
        self.growth_level = 0
        self.water_loss_time = water_loss_time
        self.growth_time = growth_time
        self.fruit_name = fruit_name
        self.is_alive = True
        self.has_fruit = False
        self.last_water_loss = time.time()
        self.planting_time = time.time()

    def update(self):
        current_time = time.time()
        
        if current_time - self.last_water_loss >= self.water_loss_time:
            self.water_level -= 10
            self.last_water_loss = current_time
            
            if self.water_level <= 0:
                self.is_alive = False
                return False
                
        if self.is_alive:
            growth_progress = (current_time - self.planting_time) / self.growth_time
            self.growth_level = min(100, growth_progress * 100)
            
            if self.growth_level >= 100:
                self.has_fruit = True
                
        return True

    def water(self):
        if self.is_alive:
            self.water_level = min(100, self.water_level + 30)

class GardenCell(tk.Frame):
    def __init__(self, master, garden, row, col):
        super().__init__(master, width=100, height=100, relief=tk.RAISED, borderwidth=1)
        self.grid_propagate(False)
        self.plant = None
        self.row = row
        self.col = col
        self.garden = garden
        
        self.canvas = tk.Canvas(self, width=100, height=100)
        self.canvas.pack(fill=tk.BOTH, expand=True)
        
        self.canvas.bind("<Button-1>", self.on_click)
        
    def on_click(self, event):
        if not self.plant:
            self.show_plant_menu()
        elif self.plant.has_fruit:
            self.harvest()
        else:
            self.water_plant()
            
    def water_plant(self):
        if self.plant and self.plant.is_alive:
            self.plant.water()
            
    def harvest(self):
        if self.plant and self.plant.has_fruit:
            self.garden.inventory[self.plant.fruit_name] = self.garden.inventory.get(self.plant.fruit_name, 0) + 1
            self.plant = None
            self.garden.update_inventory_display()

    def show_plant_menu(self):
        menu = tk.Menu(self, tearoff=0)
        
        for plant_name, count in self.garden.inventory.items():
            if count > 0:
                menu.add_command(
                    label=f"Посадити {plant_name} ({count})",
                    command=lambda p=plant_name: self.plant_seed(p)
                )
                
        menu.add_separator()
        
        for plant_name in self.garden.plants_data:
            menu.add_command(
                label=f"Купити і посадити {plant_name}",
                command=lambda p=plant_name: self.plant_new(p)
            )
            
        menu.post(self.winfo_rootx(), self.winfo_rooty())

    def plant_seed(self, plant_name):
        if self.garden.inventory[plant_name] > 0:
            self.garden.inventory[plant_name] -= 1
            self.garden.update_inventory_display()
            plant_data = self.garden.plants_data[plant_name]
            self.plant = Plant(plant_name, **plant_data)
            
    def plant_new(self, plant_name):
        plant_data = self.garden.plants_data[plant_name]
        self.plant = Plant(plant_name, **plant_data)
            
    def update_display(self):
        self.canvas.delete("all")
        
        if self.plant:
            if not self.plant.is_alive:
                self.canvas.create_text(50, 50, text="💀", font=("TkDefaultFont", 20))
                self.plant = None
                return
                
            # Відображення рівня води
            water_height = 80 * (self.plant.water_level / 100)
            self.canvas.create_rectangle(10, 80, 30, 80 - water_height, fill="blue")
            
            # Відображення росту
            growth_height = 80 * (self.plant.growth_level / 100)
            self.canvas.create_rectangle(40, 80, 60, 80 - growth_height, fill="green")
            
            # Текст з інформацією
            self.canvas.create_text(50, 90, text=f"{self.plant.name}", font=("TkDefaultFont", 8))
            
            # Відображення рослини
            plant_symbol = "🌱"
            if self.plant.growth_level >= 50:
                plant_symbol = "🌿"
            if self.plant.has_fruit:
                plant_symbol = {"Томат": "🍅", "Морква": "🥕", "Картопля": "🥔"}[self.plant.name]
                
            self.canvas.create_text(50, 30, text=plant_symbol, font=("TkDefaultFont", 20))

class VirtualGarden(tk.Tk):
    def __init__(self):
        super().__init__()
        
        self.title("Віртуальний Сад")
        self.geometry("800x600")
        
        self.plants_data = {
            "Томат": {"water_loss_time": 40, "growth_time": 120, "fruit_name": "Томат"},
            "Морква": {"water_loss_time": 60, "growth_time": 180, "fruit_name": "Морква"},
            "Картопля": {"water_loss_time": 90, "growth_time": 240, "fruit_name": "Картопля"}
        }
        self.inventory = {}
        
        # Створюємо головний контейнер
        self.main_container = tk.Frame(self)
        self.main_container.pack(expand=True, fill='both', padx=20, pady=20)
        
        self.create_garden()
        self.create_inventory_display()
        self.create_info_display()
        self.start_update_thread()
        
    def create_garden(self):
        self.garden_frame = tk.Frame(self.main_container)
        self.garden_frame.pack(pady=20)
        
        self.cells = []
        for row in range(2):
            row_cells = []
            for col in range(8):
                cell = GardenCell(self.garden_frame, self, row, col)
                cell.grid(row=row, column=col, padx=2, pady=2)
                row_cells.append(cell)
            self.cells.append(row_cells)
                
    def create_inventory_display(self):
        self.inventory_frame = tk.LabelFrame(self.main_container, text="Інвентар", padx=10, pady=5)
        self.inventory_frame.pack(fill='x', pady=10)
        self.inventory_label = tk.Label(self.inventory_frame, text="Порожньо")
        self.inventory_label.pack()
        
    def create_info_display(self):
        self.info_frame = tk.LabelFrame(self.main_container, text="Інформація", padx=10, pady=5)
        self.info_frame.pack(fill='x', pady=10)
        
        info_text = """
        🌱 - Натисніть на порожню клітинку, щоб посадити рослину
        💧 - Натисніть на рослину, щоб полити її
        🍅 - Натисніть на стиглу рослину, щоб зібрати плоди
        """
        self.info_label = tk.Label(self.info_frame, text=info_text, justify=tk.LEFT)
        self.info_label.pack(anchor='w')
        
    def update_inventory_display(self):
        if not self.inventory:
            self.inventory_label.config(text="Порожньо")
        else:
            inventory_text = ", ".join([f"{item}: {count}" for item, count in self.inventory.items()])
            self.inventory_label.config(text=inventory_text)
        
    def start_update_thread(self):
        def update_loop():
            while True:
                for row in self.cells:
                    for cell in row:
                        if cell.plant:
                            cell.plant.update()
                        cell.update_display()
                time.sleep(0.1)
                
        thread = threading.Thread(target=update_loop, daemon=True)
        thread.start()

if __name__ == "__main__":
    app = VirtualGarden()
    app.mainloop()