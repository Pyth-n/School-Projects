package models;


import java.io.Serializable;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

/**
 * Created by CarlosIribar on 10/31/17.
 */

public class Item implements Serializable {

    private long id;
    private String name;
    private String notes;
    private Date createdDate;
    private long listId;
    private Date dueDate;
    private Integer priority;
    private String priorityName;
    private String tags;
    private List<String> imagesUrls;
    private Boolean isCompleted;

    /**
     *  Item Constructor
     * @param name
     */
    public Item(String name) {
        this.name = name;
    }

    /**
     *  Get Id
     * @return
     */
    public long getId() {
        return id;
    }

    /**
     *  Set Id
     * @param id
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     *  Get Name
     * @return
     */
    public String getName() {
        return name;
    }

    /**
     * Set Name
     * @param name
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Get notes
     * @return
     */
    public String getNotes() {
        return notes;
    }

    /**
     * Set Notes
     * @param notes
     */
    public void setNotes(String notes) {
        this.notes = notes;
    }

    /**
     * Get Created Date
     * @return
     */
    public Date getCreatedDate() {
        return createdDate;
    }

    /**
     * Set Created Date
     * @param createdDate
     */
    public void setCreatedDate(Date createdDate) {
        this.createdDate = createdDate;
    }

    /**
     * Get Due Date
     * @return
     */
    public Date getDueDate() {
        return dueDate;
    }

    /**
     * Set Due Date
     * @param dueDate
     */
    public void setDueDate(Date dueDate) {
        this.dueDate = dueDate;
    }

    /**
     * Get Priority
     * @return
     */
    public Integer getPriority() {
        return priority;
    }

    /**
     * Set Priority
     * @param priority
     */
    public void setPriority(Integer priority) {
        this.priority = priority;
    }

    /**
     * Get Tags
     * @return
     */
    public String getTags() {
        return tags;
    }

    /**
     * Get Image Urls
     * @return
     */
    public List<String> getImagesUrls() {
        return imagesUrls;
    }

    /**
     * Set ImagesUrls
     * @param imagesUrls
     */
    public void setImagesUrls(List<String> imagesUrls) {
        this.imagesUrls = imagesUrls;
    }

    /**
     * Get Completed
     * @return
     */
    public Boolean getCompleted() {
        return isCompleted;
    }

    /**
     * Set Completed
     * @param completed
     */
    public void setCompleted(Boolean completed) {
        isCompleted = completed;
    }

    /**
     * Get List Id
     * @return
     */
    public long getListId() {
        return listId;
    }

    /**
     * Set List Id
     * @param listId
     */
    public void setListId(long listId) {
        this.listId = listId;
    }

    /**
     * Get Priority Name
     * @return
     */
    public String getPriorityName() {
        return priorityName;
    }

    /**
     * Set Priority Name
     * @param priorityName
     */
    public void setPriorityName(String priorityName) {
        this.priorityName = priorityName;
    }

    /**
     * Set Tags
     * @param tags
     */
    public void setTags(String tags) {
        this.tags = tags;
    }

    /***
     * Get Created Date in a String format
     * @return
     */
    public String getCreatedDateString() {
        if(createdDate == null) {
            return null;
        }
        SimpleDateFormat spf= new SimpleDateFormat("yyyy MMM dd  hh:mm");
        return spf.format(createdDate);
    }

}
