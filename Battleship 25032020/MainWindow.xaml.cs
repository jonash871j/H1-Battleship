using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Battleship_25032020
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private GUI.ImageMatrix imageMatrix;
        private Game.Manager game;
        private Game.ShipType shipChoice = Game.ShipType.ShipCarrier;
        private Game.ShipDirection shipDirection = Game.ShipDirection.Horizontal;

        public MainWindow()
        {
            InitializeComponent();
            NewGame(10, 10);
        }

        private void NewGame(int width, int height)
        {       
            void Import(int amount, Game.Field tile, string path, bool useNumber)
            {
                for (int i = 0; i < amount; i++)
                {
                    if (useNumber == true)
                        imageMatrix.AddImage((int)tile + i, "./Resources/" + path + i + ".png");
                    else
                        imageMatrix.AddImage((int)tile + i, "./Resources/" + path + ".png");
                }
            }

            bn_player_field.IsChecked = true;
            bn_ai_field.IsChecked = false;

            game = new Game.Manager(width, height);
            game.AIPlaceShip();

            imageMatrix = new GUI.ImageMatrix(grid_game, game.MapUser.Array, 64, 64);
            imageMatrix.OnButtonClicked += bn_game_map_Clicked;
            imageMatrix.Initialize(new SolidColorBrush(Color.FromArgb(0, 0, 0, 0)), new SolidColorBrush(Color.FromArgb(255, 0, 0, 0)));

            Import(1, Game.Field.Water, "Other/spr_empty", false);
            Import(1, Game.Field.Miss, "Other/spr_cross", false);
            Import(1, Game.Field.Hit, "Other/spr_fragment", false);
            Import(3, Game.Field.H_ShipCarrier, "Carrier/spr_H_", true);
            Import(3, Game.Field.V_ShipCarrier, "Carrier/spr_V_", true);
            Import(3, Game.Field.H_ShipBattle, "Battleship/spr_H_", true);
            Import(3, Game.Field.V_ShipBattle, "Battleship/spr_V_", true);
            Import(2, Game.Field.H_ShipDestroyer, "Destroyer/spr_H_", true);
            Import(2, Game.Field.V_ShipDestroyer, "Destroyer/spr_V_", true);
            Import(2, Game.Field.H_ShipSubmarine, "Submarine/spr_H_", true);
            Import(2, Game.Field.V_ShipSubmarine, "Submarine/spr_V_", true);
            Import(2, Game.Field.H_ShipCruiser, "Cruiser/spr_H_", true);
            Import(2, Game.Field.V_ShipCruiser, "Cruiser/spr_V_", true);


            imageMatrix.UpdateAll();
            grid_game_background.Width = imageMatrix.Width;
            grid_game_background.Height = imageMatrix.Height;
        }

        private void bn_game_map_Clicked(object sender, EventArgs e)
        {
           if (bn_player_field.IsChecked == true)
                game.UserPlaceShip(shipChoice, imageMatrix.ClickedCellX, imageMatrix.ClickedCellY, shipDirection);
            else
            {
                if (game.ReadyToAttack == true)
                {
                    game.UserAttack(imageMatrix.ClickedCellX, imageMatrix.ClickedCellY);
                    game.AIRandomAttack();
                }
            }
            if (game.ReadyToAttack == true)
                sp_gameMenu.Visibility = Visibility.Hidden;

            if (game.OnWin() == true)
            {
                MessageBox.Show("Game is over...");
                mi_new_game_Click(e, null);
            }

            imageMatrix.UpdateAll();
        }

        private void mi_new_game_Click(object sender, RoutedEventArgs e)
        {
            sp_gameMenu.Visibility = Visibility.Visible;
            imageMatrix.Delete();
            NewGame(10, 10);
        }

        private void mi_quit_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void bn_player_field_Click(object sender, RoutedEventArgs e)
        {
            imageMatrix.UpdateArray(game.MapUser.Array);
            bn_player_field.IsChecked = true;
            bn_ai_field.IsChecked = false;
        }

        private void bn_ai_field_Click(object sender, RoutedEventArgs e)
        {
            imageMatrix.UpdateArray(game.MapAI.Array);
            bn_player_field.IsChecked = false;
            bn_ai_field.IsChecked = true;
        }

        private void bn_attack_Click(object sender, RoutedEventArgs e)
        {
            game.AIRandomAttack();
            imageMatrix.UpdateAll();
        }

        private void bn_carrier_Click(object sender, RoutedEventArgs e)
        {
            shipChoice = Game.ShipType.ShipCarrier;
        }

        private void bn_battleship_Click(object sender, RoutedEventArgs e)
        {
            shipChoice = Game.ShipType.ShipBattle;
        }

        private void bn_destoryer_Click(object sender, RoutedEventArgs e)
        {
            shipChoice = Game.ShipType.ShipDestroyer;
        }

        private void bn_submarine_Click(object sender, RoutedEventArgs e)
        {
            shipChoice = Game.ShipType.ShipSubmarine;
        }

        private void bn_cruiser_Click(object sender, RoutedEventArgs e)
        {
            shipChoice = Game.ShipType.ShipCruiser;
        }

        private void bn_clear_Click(object sender, RoutedEventArgs e)
        {
            if (MessageBox.Show("Are you sure you want to clear your field?", "Warning", MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
            {
                game.UserClearMap();
                imageMatrix.UpdateAll();
            }
        }

        private void bn_roatate_Click(object sender, RoutedEventArgs e)
        {
            switch(shipDirection)
            {
            case Game.ShipDirection.Horizontal:
                shipDirection = Game.ShipDirection.Vertical;
                tbl_direction.Text = "    Vertical";
                break;
            case Game.ShipDirection.Vertical:
                shipDirection = Game.ShipDirection.Horizontal;
                tbl_direction.Text = " Horizontal";
                break;
            }
        }
    }
}