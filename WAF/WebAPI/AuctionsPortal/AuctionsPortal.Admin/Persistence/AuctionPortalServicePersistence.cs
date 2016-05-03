using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading.Tasks;
using AuctionsPortal.Data;

namespace AuctionsPortal.Admin.Persistence
{
    class AuctionPortalServicePersistence : IAuctionsPortalPesistence
    {

        private HttpClient _client;

        public AuctionPortalServicePersistence(String baseAddress)
        {
            _client = new HttpClient(); // a szolgáltatás kliense
            _client.BaseAddress = new Uri(baseAddress); // megadjuk neki a címet
        }


        public async Task<bool> CreateItemImageAsync(ImageDTO image)
        {
            try
            {
                HttpResponseMessage response = await _client.PostAsJsonAsync("api/images/", image); // elküldjük a képet
                if (response.IsSuccessStatusCode)
                {
                    image.Id = await response.Content.ReadAsAsync<Int32>(); // a válaszüzenetben megkapjuk az azonosítót
                }
                return response.IsSuccessStatusCode;
            }
            catch (Exception ex)
            {
                throw new PersistenceUnavailableException(ex);
            }
        }

        public async Task<bool> CreateItemAsync(ItemDTO item)
        {
            try
            {
                HttpResponseMessage response = await _client.PostAsJsonAsync("api/items/", item); // az értékeket azonnal JSON formátumra alakítjuk
                item.Id = (await response.Content.ReadAsAsync<ItemDTO>()).Id; // a válaszüzenetben megkapjuk a végleges azonosítót
                return response.IsSuccessStatusCode;
            }
            catch (Exception ex)
            {
                throw new PersistenceUnavailableException(ex);
            }
        }

        public async Task<bool> DeleteItemImageAsync(ImageDTO image)
        {
            try
            {
                HttpResponseMessage response = await _client.DeleteAsync("api/images/" + image.Id);
                return response.IsSuccessStatusCode;
            }
            catch (Exception ex)
            {
                throw new PersistenceUnavailableException(ex);
            }
        }

        public async Task<bool> LoginAsync(string userName, string userPassword)
        {
            try
            {
                HttpResponseMessage response = await _client.GetAsync("api/account/login/" + userName +  "/" + userPassword);
                return response.IsSuccessStatusCode; // a művelet eredménye megadja a bejelentkezés sikeressségét
            }
            catch (Exception ex)
            {
                throw new PersistenceUnavailableException(ex);
            }
        }

        public async Task<bool> LogoutAsync()
        {
            try
            {
                HttpResponseMessage response = await _client.GetAsync("api/account/logout");
                return !response.IsSuccessStatusCode;
            }
            catch (Exception ex)
            {
                throw new PersistenceUnavailableException(ex);
            }
        }

        public async Task<IEnumerable<CategoryDTO>> ReadCategoriesAsync()
        {
            try
            {
                HttpResponseMessage response = await _client.GetAsync("api/category/");
                if (response.IsSuccessStatusCode)
                {
                    return await response.Content.ReadAsAsync<IEnumerable<CategoryDTO>>();
                }
                else
                {
                    throw new PersistenceUnavailableException("Service returned response: " + response.StatusCode);
                }
            }
            catch (Exception ex)
            {
                throw new PersistenceUnavailableException(ex);
            }
        }

        public async Task<IEnumerable<ItemDTO>> ReadItemsAsync()
        {
            try
            {
                // a kéréseket a kliensen keresztül végezzük
                HttpResponseMessage response = await _client.GetAsync("api/items/advertisements");
                if (response.IsSuccessStatusCode) // amennyiben sikeres a művelet
                {
                    IEnumerable<ItemDTO> items = await response.Content.ReadAsAsync<IEnumerable<ItemDTO>>();
                    // a tartalmat JSON formátumból objektumokká alakítjuk

                    // képek lekérdezése:
                    foreach (ItemDTO item in items)
                    {
                        response = await _client.GetAsync("api/images/item/" + item.Id);
                        if (response.IsSuccessStatusCode)
                        {
                            item.Images = (await response.Content.ReadAsAsync<IEnumerable<ImageDTO>>()).ToList();
                        }
                    }

                    return items;
                }
                else
                {
                    throw new PersistenceUnavailableException("Service returned response: " + response.StatusCode);
                }
            }
            catch (Exception ex)
            {
                throw new PersistenceUnavailableException(ex);
            }
        }

        public async Task<bool> UpdateItemAsync(ItemDTO item)
        {
            try
            {
                HttpResponseMessage response = await _client.PutAsJsonAsync("api/items/", item);
                return response.IsSuccessStatusCode;
            }
            catch (Exception ex)
            {
                throw new PersistenceUnavailableException(ex);
            }
        }
    }
}
