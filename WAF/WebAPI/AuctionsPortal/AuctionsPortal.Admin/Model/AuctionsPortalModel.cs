using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AuctionsPortal.Data;
using AuctionsPortal.Admin.Persistence;

namespace AuctionsPortal.Admin.Model
{
    class AuctionsPortalModel : IAuctionsPortalModel
    {
        /// <summary>
        /// Adat állapotjelzések.
        /// </summary>
        private enum DataFlag
        {
            Create,
            Update,
            Delete
        }

        private IAuctionsPortalPesistence _persistence;
        private List<ItemDTO> _items;
        private Dictionary<ItemDTO, DataFlag> _itemFlags;
        private Dictionary<ImageDTO, DataFlag> _imageFlags;
        private List<CategoryDTO> _categories;


        /// <summary>
        /// Modell példányosítása.
        /// </summary>
        /// <param name="persistence">A perzisztencia.</param>
        public AuctionsPortalModel(IAuctionsPortalPesistence persistence)
        {
            if (persistence == null)
                throw new ArgumentNullException("persistence");

            IsUserLoggedIn = false;
            _persistence = persistence;
        }

        public IReadOnlyList<CategoryDTO> Categories
        {
            get
            {
                return _categories;
            }
        }

        public bool IsUserLoggedIn
        {
            get;
            private set;
        }

        public IReadOnlyList<ItemDTO> Items
        {
            get
            {
                return _items;
            }
        }

        public event EventHandler<ItemEventArgs> ItemChanged;

        public void CreateImage(int itemId, byte[] image_)
        {
            ItemDTO item = _items.FirstOrDefault(i => i.Id == itemId);
            if (item == null)
                throw new ArgumentException("The building does not exist.", "buildingId");

            // létrehozzuk a képet
            ImageDTO image = new ImageDTO
            {
                Id = _items.Max(b => b.Images.Any() ? b.Images.Max(im => im.Id) : 0) + 1,
                ItemId = itemId,
                Image = image_
            };

            // hozzáadjuk
            item.Images.Add(image);
            _imageFlags.Add(image, DataFlag.Create);

            // jellezzük a változást
            OnItemChanged(item.Id);
        }

        public void CreateItem(ItemDTO item)
        {
            if (item == null)
                throw new ArgumentNullException("item");
            if (_items.Contains(item))
                throw new ArgumentException("The item is already in the collection.", "building");

            item.Id = (_items.Count > 0 ? _items.Max(b => b.Id) : 0) + 1; // generálunk egy új, ideiglenes azonosítót (nem fog átkerülni a szerverre)
            _itemFlags.Add(item, DataFlag.Create);
            _items.Add(item);
        }

        public void DeleteImage(ImageDTO image)
        {
            if (image == null)
                throw new ArgumentNullException("image");

            // megkeressük a képet
            foreach (ItemDTO item in _items)
            {
                if (!item.Images.Contains(image))
                    continue;

                // kezeljük az állapotjelzéseket is
                if (_imageFlags.ContainsKey(image))
                    _imageFlags.Remove(image);
                else
                    _imageFlags.Add(image, DataFlag.Delete);

                // töröljük a képet
                item.Images.Remove(image);

                // jellezzük a változást
                OnItemChanged(item.Id);

                return;
            }

            // ha idáig eljutott, akkor nem sikerült képet törölni+
            throw new ArgumentException("The image does not exist.", "image");
        }

        public async Task LoadAsync()
        {
            // adatok
            _items = (await _persistence.ReadItemsAsync()).ToList();
            _categories = (await _persistence.ReadCategoriesAsync()).ToList();

            // állapotjelzések
            _itemFlags = new Dictionary<ItemDTO, DataFlag>();
            _imageFlags = new Dictionary<ImageDTO, DataFlag>();
        }

        public async Task SaveAsync()
        {
            // tárgyak
            List<ItemDTO> itemsToSave = _itemFlags.Keys.ToList();

            foreach (ItemDTO item in itemsToSave)
            {
                Boolean result = true;

                // az állapotjelzőnek megfelelő műveletet végezzük el
                switch (_itemFlags[item])
                {
                    case DataFlag.Create:
                        result = await _persistence.CreateItemAsync(item);
                        break;
                    case DataFlag.Update:
                        result = await _persistence.UpdateItemAsync(item);
                        break;
                }

                if (!result)
                    throw new InvalidOperationException("Operation " + _itemFlags[item] + " failed on item " + item.Id);

                // ha sikeres volt a mentés, akkor törölhetjük az állapotjelzőt
                _itemFlags.Remove(item);
            }

            // képek
            List<ImageDTO> imagesToSave = _imageFlags.Keys.ToList();

            foreach (ImageDTO image in imagesToSave)
            {
                Boolean result = true;

                switch (_imageFlags[image])
                {
                    case DataFlag.Create:
                        result = await _persistence.CreateItemImageAsync(image);
                        break;
                    case DataFlag.Delete:
                        result = await _persistence.DeleteItemImageAsync(image);
                        break;
                }

                if (!result)
                    throw new InvalidOperationException("Operation " + _imageFlags[image] + " failed on image " + image.Id);

                // ha sikeres volt a mentés, akkor törölhetjük az állapotjelzőt
                _imageFlags.Remove(image);
            }
        }


        public async Task<bool> LoginAsync(string userName, string userPassword)
        {
            IsUserLoggedIn = await _persistence.LoginAsync(userName, userPassword);
            return IsUserLoggedIn;
        }


        public async Task<bool> LogoutAsync()
        {
            if (!IsUserLoggedIn)
                return true;

            IsUserLoggedIn = !(await _persistence.LogoutAsync());
            if(!IsUserLoggedIn)
            {
                _items.Clear();
                _categories.Clear();
            }
                

            return IsUserLoggedIn;
        }

        public async Task<bool> RegisterAsync(AdvatiserDTO advatiser)
        {
            return await _persistence.RegisterAsync(advatiser);

        }

        public void CloseItem(Int32 itemId)
        {
            // keresés azonosító alapján
            ItemDTO itemToClose = _items.FirstOrDefault(i => i.Id == itemId);
            if (itemToClose.Biddings.Count == 0)
                return;

            itemToClose.CloseDate = DateTime.Now;

            _itemFlags[itemToClose] = DataFlag.Update;

            // jelezzük a változást
            OnItemChanged(itemId);
    }

        public void UpdateItem(ItemDTO item)
        {
            if (item == null)
                throw new ArgumentNullException("item");

            // keresés azonosító alapján
            ItemDTO itemToModify = _items.FirstOrDefault(i => i.Id == item.Id);

            if (itemToModify == null)
                throw new ArgumentException("The item does not exist.", "item");

            // módosítások végrehajtása
            itemToModify.Category = item.Category;
            itemToModify.Description = item.Description;
            itemToModify.Name = item.Name;
            itemToModify.CloseDate = item.CloseDate;

            // külön állapottal jelezzük, ha egy adat újonnan hozzávett
            if (_itemFlags.ContainsKey(itemToModify) && _itemFlags[itemToModify] == DataFlag.Create)
            {
                _itemFlags[itemToModify] = DataFlag.Create;
            }
            else
            {
                _itemFlags[itemToModify] = DataFlag.Update;
            }

            // jelezzük a változást
            OnItemChanged(item.Id);
        }


        private void OnItemChanged(Int32 id)
        {
            if (ItemChanged != null)
                ItemChanged(this, new ItemEventArgs { ItemId =  id});
        }


    }
}
