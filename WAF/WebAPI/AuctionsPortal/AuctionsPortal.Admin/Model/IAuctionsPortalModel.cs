using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AuctionsPortal.Data;

namespace AuctionsPortal.Admin.Model
{
    public interface IAuctionsPortalModel
    {
        /// <summary>
        /// kategórák lekérdezése.
        /// </summary>
        IReadOnlyList<CategoryDTO> Categories { get; }

        /// <summary>
        /// Tárgyak lekérdezése.
        /// </summary>
        IReadOnlyList<ItemDTO> Items { get; }

        /// <summary>
        /// Bejelentkezettség lekérdezése.
        /// </summary>
        Boolean IsUserLoggedIn { get; }

        /// <summary>
        /// Tárgyváltozás eseménye.
        /// </summary>
        event EventHandler<ItemEventArgs> ItemChanged;

        /// <summary>
        /// Tárgy létrehozása.
        /// </summary>
        /// <param name="item">Az épület.</param>
        void CreateItem(ItemDTO item);

        /// <summary>
        /// Kép létrehozása.
        /// </summary>
        /// <param name="itemId">Épület azonosító.</param>
        /// <param name="image">Kis kép.</param>
        void CreateImage(Int32 itemId, Byte[] image);

        /// <summary>
        /// Tárgy lezárása.
        /// </summary>
        /// <param name="building">Az épület.</param>
        void CloseItem(Int32 itemId);

        /// <summary>
        /// Kép törlése.
        /// </summary>
        /// <param name="image">A kép.</param>
        void DeleteImage(ImageDTO image);

        /// <summary>
        /// Adatok betöltése.
        /// </summary>
        Task LoadAsync();

        /// <summary>
        /// Adatok mentése.
        /// </summary>
        Task SaveAsync();

        /// <summary>
        /// Bejelentkezés.
        /// </summary>
        /// <param name="userName">Felhasználónév.</param>
        /// <param name="userPassword">Jelszó.</param>
        Task<Boolean> LoginAsync(String userName, String userPassword);

        /// <summary>
        /// Kijelentkezés.
        /// </summary>
        Task<Boolean> LogoutAsync();
    }
}
