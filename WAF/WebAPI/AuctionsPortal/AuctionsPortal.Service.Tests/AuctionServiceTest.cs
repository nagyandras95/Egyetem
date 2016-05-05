using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Linq;
using Moq;
using System.Data.Entity;
using AuctionsPortal.Service.Models;
using System.Collections.Generic;

namespace AuctionsPortal.Service.Tests
{
    [TestClass]
    class AuctionServiceTest
    {

        private List<Category> _CategoryData;
        private List<Item> _ItemData;
        private List<ItemImage> _ItemImageData;
        private Mock<DbSet<Category>> _CategoryMock;
        private Mock<DbSet<Item>> _ItemMock;
        private Mock<DbSet<ItemImage>> _ItemImageMock;
        private Mock<AuctionsPortalEntities> _entityMock;
        private AuctionService _service;

        [TestInitialize]
        public void Initialize()
        {
            // adatok inicializációja
            _CategoryData = new List<Category>
            {
                new Category { CategoryId = 1, CatgoryName = "TESTCategory" }
            };

            _ItemData = new List<Item>
            {
                new Item { ItemId = 1, CategoryId = _CategoryData[0].Id, Category = _CategoryData[0], Name = "TESTItem1" },
                new Item { ItemId = 2, CategoryId = _CategoryData[0].Id, Category = _CategoryData[0], Name = "TESTItem2" },
                new Item { ItemId = 3, CategoryId = _CategoryData[0].Id, Category = _CategoryData[0], Name = "TESTItem3" }
            };

            _ItemImageData = new List<ItemImage>
            {
            };

            // entitásmodell inicializációja, amihez le kell generálnunk az adatokhoz tartozó gyűjteményeket (táblákat) is
            // ehhez néhány alap információt be kell állítanunk, lehetővé téve, hogy az adatok lekérdezését biztosítsa a rendszer
            IQueryable<Category> queryableCategoryData = _CategoryData.AsQueryable();
            _CategoryMock = new Mock<DbSet<Category>>();
            _CategoryMock.As<IQueryable<Category>>().Setup(mock => mock.ElementType).Returns(queryableCategoryData.ElementType);
            _CategoryMock.As<IQueryable<Category>>().Setup(mock => mock.Expression).Returns(queryableCategoryData.Expression);
            _CategoryMock.As<IQueryable<Category>>().Setup(mock => mock.Provider).Returns(queryableCategoryData.Provider);
            _CategoryMock.As<IQueryable<Category>>().Setup(mock => mock.GetEnumerator()).Returns(_CategoryData.GetEnumerator()); // a korábban megadott listát fogjuk visszaadni

            Item deletedItem = null;

            IQueryable<Item> queryableItemData = _ItemData.AsQueryable();
            _ItemMock = new Mock<DbSet<Item>>();
            _ItemMock.As<IQueryable<Item>>().Setup(mock => mock.ElementType).Returns(queryableItemData.ElementType);
            _ItemMock.As<IQueryable<Item>>().Setup(mock => mock.Expression).Returns(queryableItemData.Expression);
            _ItemMock.As<IQueryable<Item>>().Setup(mock => mock.Provider).Returns(queryableItemData.Provider);
            _ItemMock.As<IQueryable<Item>>().Setup(mock => mock.GetEnumerator()).Returns(_ItemData.GetEnumerator());

            _ItemMock.Setup(mock => mock.Add(It.IsAny<Item>())).Callback<Item>(Item => { _ItemData.Add(Item); }).Returns(_ItemData.Last()); // beállítjuk, hogy mi történjen épület hozzáadásakor

            _ItemMock.Setup(mock => mock.Remove(It.IsAny<Item>())).Callback<Item>(Item =>
            {
                if (_ItemData.Contains(deletedItem))
                    deletedItem = Item;

                _ItemData.Remove(Item);
            }).Returns(deletedItem); // beállítjuk, hogy mi történjen épület törlésekor

            _ItemMock.Setup(mock => mock.Include(It.IsAny<String>())).Returns(_ItemMock.Object); // azt is be kell állítanunk, hogy tábla csatolása esetén mi történjen       

            IQueryable<ItemImage> queryableItemImageData = _ItemImageData.AsQueryable();
            _ItemImageMock = new Mock<DbSet<ItemImage>>();
            _ItemImageMock.As<IQueryable<ItemImage>>().Setup(mock => mock.ElementType).Returns(queryableItemImageData.ElementType);
            _ItemImageMock.As<IQueryable<ItemImage>>().Setup(mock => mock.Expression).Returns(queryableItemImageData.Expression);
            _ItemImageMock.As<IQueryable<ItemImage>>().Setup(mock => mock.Provider).Returns(queryableItemImageData.Provider);
            _ItemImageMock.As<IQueryable<ItemImage>>().Setup(mock => mock.GetEnumerator()).Returns(_ItemImageData.GetEnumerator());

            // a szimulált entitásmodell csak ezt a két táblát fogja tartalmazni
            _entityMock = new Mock<AuctionsPortalEntities>();
            _entityMock.Setup<DbSet<Item>>(entity => entity.Item).Returns(_ItemMock.Object);
            _entityMock.Setup<DbSet<Category>>(entity => entity.Category).Returns(_CategoryMock.Object);
            _entityMock.Setup<DbSet<ItemImage>>(entity => entity.ItemImage).Returns(_ItemImageMock.Object);


            _service = new AuctionService(_entityMock.Object); // ehhez csatlakozik a kliens

        }
}
