using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using AuctionsPortal.Data;

namespace AuctionsPortal.Admin.Persistence
{
    public interface IAuctionsPortalPesistence
    {

        /// <summary>
        /// Tárgyak olvasása.
        /// </summary>
        Task<IEnumerable<ItemDTO>> ReadItemsAsync();

        /// <summary>
        /// Kategórák olvasása.
        /// </summary>
        Task<IEnumerable<CategoryDTO>> ReadCategoriesAsync();

        /// <summary>
        /// Tárgy létrehozása.
        /// </summary>
        /// <param name="building">Épület.</param>
        Task<Boolean> CreateItemAsync(ItemDTO item);

        /// <summary>
        /// Tárgy módosítása.
        /// </summary>
        /// <param name="building">Épület.</param>
        Task<Boolean> UpdateItemAsync(ItemDTO item);


        /// <summary>
        /// Épületkép létrehozása.
        /// </summary>
        /// <param name="image">Épületkép.</param>
        Task<Boolean> CreateItemImageAsync(ImageDTO image);

        /// <summary>
        /// Tárgykép törlése.
        /// </summary>
        /// <param name="image">Épületkép.</param>
        Task<Boolean> DeleteItemImageAsync(ImageDTO image);

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
