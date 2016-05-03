using System;
using System.Linq;
using System.Web.Http;
using AuctionsPortal.Service.Models;
using AuctionsPortal.Data;
using System.Diagnostics;
using System.Web;

namespace AuctionsPortal.Service.Controllers
{
    [RoutePrefix("api/cetgory")]
    public class CategoryController : ApiController
    {
        private AuctionsPortalEntities _entities;

        public CategoryController()
        {
            _entities = new AuctionsPortalEntities();
        }

        ~CategoryController()
        {
            Dispose(false);
        }

        [System.Web.Http.HttpGet]
        public IHttpActionResult GetCategories()
        {
            return Ok(_entities.Category.ToList().Select(category => new CategoryDTO
            {
                Name = category.CatgoryName,
                Id = category.CategoryId
        
             }));
        }

    }
}