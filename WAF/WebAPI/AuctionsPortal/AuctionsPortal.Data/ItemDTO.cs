using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AuctionsPortal.Data
{
    public class ItemDTO
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public int StartingCall { get; set; }
        public int Amount { get; set; }
        public System.DateTime StartDate { get; set; }
        public System.DateTime CloseDate { get; set; }
        public IList<BiddingDTO> Biddings { get; set; }
        public IList<ImageDTO> Images { get; set; }        
        public CategoryDTO Category { get; set; }       
        public AdvatiserDTO Advatiser { get; set; }     

        public ItemDTO()
        {
             Biddings = new List<BiddingDTO>();
             Images = new List<ImageDTO>();
        }
    }
}
