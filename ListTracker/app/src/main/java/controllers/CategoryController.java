package controllers;

import android.content.Context;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import database.CategoryCRUD;
import database.ListTrackerDataSource;
import models.Category;
import models.ItemList;

/**
 * Created by CarlosIribar on 11/9/17.
 */

public class CategoryController implements Serializable {

    private CategoryCRUD controller;

    public CategoryController(Context context) {
        controller = new CategoryCRUD(context);
    }


    public List<String> getCategoryNames(Context context) {
        List<String> categoriesNames = new ArrayList<>();
        List<Category> categories =  controller.getCategories();
        for (Category category : categories) {
            categoriesNames.add(category.getName());
        }
        return categoriesNames;
    }

    public long saveCategory(Category category) {
        return controller.saveItemList(category);
    }
}
