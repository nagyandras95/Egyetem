using System;
using AuctionsPortal.Admin.Model;
using AuctionsPortal.Admin.Persistence;
using AuctionsPortal.Data;
using System.Collections.Generic;
using System.Linq;
using System.Collections.ObjectModel;
using System.Text;
using System.Threading.Tasks;

namespace AuctionsPortal.Admin.ViewModel
{
    class MainViewModel : ViewModelBase
    {
        private IAuctionsPortalModel _model;
        private ObservableCollection<ItemDTO> _item;
        private ObservableCollection<CategoryDTO> _categories;
        private ItemDTO _selcetedItem;
        private Boolean _isLoaded;

        /// <summary>
        /// Tárgyak lekérdezése.
        /// </summary>
        public ObservableCollection<ItemDTO> Items
        {
            get { return _item; }
            private set
            {
                if (_item != value)
                {
                    _item = value;
                    OnPropertyChanged();
                }
            }
        }

        /// <summary>
        /// Épületek lekérdezése.
        /// </summary>
        public ObservableCollection<CategoryDTO> Categories
        {
            get { return _categories; }
            private set
            {
                if (_categories != value)
                {
                    _categories = value;
                    OnPropertyChanged();
                }
            }
        }

        /// <summary>
        /// Betöltöttség lekérdezése.
        /// </summary>
        public Boolean IsLoaded
        {
            get { return _isLoaded; }
            private set
            {
                if (_isLoaded != value)
                {
                    _isLoaded = value;
                    OnPropertyChanged();
                }
            }
        }

        /// <summary>
        /// Kijelölt épület lekérdezése, vagy beállítása.
        /// </summary>
        public ItemDTO SelectedItem
        {
            get { return _selcetedItem; }
            set
            {
                if (_selcetedItem != value)
                {
                    _selcetedItem = value;
                    OnPropertyChanged();
                }
            }
        }

        /// <summary>
        /// Szerkesztett tárgy lekérdezése.
        /// </summary>
        public ItemDTO EditedItem { get; private set; }

        /// <summary>
        /// Épület törlés parancsának lekérdezése.
        /// </summary>
        public DelegateCommand CreateItemCommand { get; private set; }

        /// <summary>
        /// Kép hozzáadás parancsának lekérdezése.
        /// </summary>
        public DelegateCommand CreateImageCommand { get; private set; }

        /// <summary>
        /// Módosítás parancsának lekérdezése.
        /// </summary>
        public DelegateCommand UpdateItemCommand { get; private set; }

        public DelegateCommand CloseItemCommand { get; private set; }

        /// <summary>
        /// Kép törlés parancsának lekérdezése.
        /// </summary>
        public DelegateCommand DeleteImageCommand { get; private set; }

        /// <summary>
        /// Változtatások mentése parancsának lekérdezése.
        /// </summary>
        public DelegateCommand SaveChangesCommand { get; private set; }

        /// <summary>
        /// Változtatások elvetése parancsának lekérdezése.
        /// </summary>
        public DelegateCommand CancelChangesCommand { get; private set; }

        /// <summary>
        /// Bejelentkezés parancs lekérdezése.
        /// </summary>
        public DelegateCommand LoginCommand { get; private set; }

        public DelegateCommand LogoutCommand { get; private set; }

        /// <summary>
        /// Kilépés parancsának lekérdezése.
        /// </summary>
        public DelegateCommand ExitCommand { get; private set; }

        /// <summary>
        /// Betöltés parancsának lekérdezése.
        /// </summary>
        public DelegateCommand LoadCommand { get; private set; }

        /// <summary>
        /// Mentés parancsának lekérdezése.
        /// </summary>
        public DelegateCommand SaveCommand { get; private set; }

        /// <summary>
        /// Alkalmazásból való kilépés eseménye.
        /// </summary>
        public event EventHandler ExitApplication;

        /// <summary>
        /// Bejelenktkező ablak eseménye
        /// </summary>
        public event EventHandler Login;

        /// <summary>
        /// Épület szerkesztés elindításának eseménye.
        /// </summary>
        public event EventHandler ItemEditingStarted;

        /// <summary>
        /// Épület szerkesztés befejeztének eseménye.
        /// </summary>
        public event EventHandler ItemEditingFinished;

        /// <summary>
        /// Képszerkesztés elindításának eseménye.
        /// </summary>
        public event EventHandler<ItemEventArgs> ImageEditingStarted;

        /// <summary>
        /// Nézetmodell példányosítása.
        /// </summary>
        /// <param name="model">A modell.</param>
        public MainViewModel(IAuctionsPortalModel model)
        {
            if (model == null)
                throw new ArgumentNullException("model");

            _model = model;
            _model.ItemChanged += Model_ItemChanged;
            _isLoaded = false;

            CreateItemCommand = new DelegateCommand(param =>
            {
                EditedItem = new ItemDTO();  // a szerkesztett tárgy új lesz
                OnItemEditingStarted();
            });
            CreateImageCommand = new DelegateCommand(param => OnImageEditingStarted((param as ItemDTO).Id));
            CloseItemCommand = new DelegateCommand(param => CloseItem((param as ItemDTO).Id));
            UpdateItemCommand = new DelegateCommand(param => UpdateBuilding(param as ItemDTO));
            DeleteImageCommand = new DelegateCommand(param => DeleteImage(param as ImageDTO));
            SaveChangesCommand = new DelegateCommand(param => SaveChanges());
            CancelChangesCommand = new DelegateCommand(param => CancelChanges());
            LoginCommand = new DelegateCommand(patam => OnLogin());
            LogoutCommand = new DelegateCommand(param => OnLogout());
            LoadCommand = new DelegateCommand(param => LoadAsync());
            SaveCommand = new DelegateCommand(param => SaveAsync());
            ExitCommand = new DelegateCommand(param => OnExitApplication());
        }

        private void CloseItem(Int32 id)
        {
            _model.CloseItem(id);
        }

        /// <summary>
        /// Tárgy frissítése.
        /// </summary>
        /// <param name="item">A tárgy.</param>
        private void UpdateBuilding(ItemDTO item)
        {
            if (item == null)
                return;

            EditedItem = new ItemDTO
            {
                Id = item.Id,
                Name = item.Name,
                Category = item.Category,
                Description = item.Description,
                CloseDate = item.CloseDate,
                StartDate = item.StartDate,
                StartingCall = item.StartingCall
            }; // a szerkesztett tárgy adatait áttöltjük a kijelöltből

            OnItemEditingStarted();
        }

        /// <summary>
        /// Kép törlése.
        /// </summary>
        /// <param name="image">A kép.</param>
        private void DeleteImage(ImageDTO image)
        {
            if (image == null)
                return;

            _model.DeleteImage(image);
        }

        /// <summary>
        /// Változtatások mentése.
        /// </summary>
        private void SaveChanges()
        {
            // ellenőrzések
            if (String.IsNullOrEmpty(EditedItem.Name))
            {
                OnMessageApplication("A tárgynév nincs megadva!");
                return;
            }
            if (EditedItem.Category == null)
            {
                OnMessageApplication("A kategóra nincs megadva!");
                return;
            }

            // mentés
            if (EditedItem.Id == 0) // ha új a tárgy
            {
                _model.CreateItem(EditedItem);
                Items.Add(EditedItem);
                SelectedItem = EditedItem;
            }
            else // ha már létezik az épület
            {
                //_model.UpdateItem(EditedItem);
            }

            EditedItem = null;

            OnItemEditingFinished();
        }

        /// <summary>
        /// Változtatások elvetése.
        /// </summary>
        private void CancelChanges()
        {
            EditedItem = null;
            OnItemEditingFinished();
        }

        /// <summary>
        /// Betöltés végrehajtása.
        /// </summary>
        private async void LoadAsync()
        {
            try
            {
                await _model.LoadAsync();
                Items = new ObservableCollection<ItemDTO>(_model.Items); // az adatokat egy követett gyűjteménybe helyezzük
                Categories = new ObservableCollection<CategoryDTO>(_model.Categories);
                IsLoaded = true;
            }
            catch (PersistenceUnavailableException)
            {
                OnMessageApplication("A betöltés sikertelen! Nincs kapcsolat a kiszolgálóval.");
            }
        }

        /// <summary>
        /// Mentés végreahajtása.
        /// </summary>
        private async void SaveAsync()
        {
            try
            {
                await _model.SaveAsync();
                OnMessageApplication("A mentés sikeres!");
            }
            catch (PersistenceUnavailableException)
            {
                OnMessageApplication("A mentés sikertelen! Nincs kapcsolat a kiszolgálóval.");
            }
        }

        /// <summary>
        /// Épület megváltozásának eseménykezelése.
        /// </summary>
        private void Model_ItemChanged(object sender, ItemEventArgs e)
        {
            Int32 index = Items.IndexOf(Items.FirstOrDefault(item => item.Id == e.ItemId));
            Items.RemoveAt(index); // módosítjuk a kollekciót
            Items.Insert(index, _model.Items[index]);

            SelectedItem = Items[index]; // és az aktuális épületet
        }

        /// <summary>
        /// Alkalmazásból való kilépés eseménykiváltása.
        /// </summary>
        private void OnExitApplication()
        {
            if (ExitApplication != null)
                ExitApplication(this, EventArgs.Empty);
        }

        private void OnLogin()
        {
            if (Login != null)
                Login(this, EventArgs.Empty);
        }

        private async void OnLogout()
        {
            await _model.LogoutAsync();
        }

        /// <summary>
        /// Épület szerkesztés elindításának eseménykiváltása.
        /// </summary>
        private void OnItemEditingStarted()
        {
            if (ItemEditingStarted != null)
                ItemEditingStarted(this, EventArgs.Empty);
        }



        /// <summary>
        /// Épület szerkesztés befejeztének eseménykiváltása.
        /// </summary>
        private void OnItemEditingFinished()
        {
            if (ItemEditingFinished != null)
                ItemEditingFinished(this, EventArgs.Empty);
        }

        /// <summary>
        /// Képszerkesztés elindításának eseménykiváltása.
        /// </summary>
        /// <param name="buildingId">Épület azonosító.</param>
        private void OnImageEditingStarted(Int32 itemId)
        {
            if (ImageEditingStarted != null)
                ImageEditingStarted(this, new ItemEventArgs { ItemId = itemId });
        }
    }
}
