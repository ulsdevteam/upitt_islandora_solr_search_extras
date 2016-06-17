<?php

/**
 * Implements hook_preprocess_theme().
 */
function upitt_solr_search_extras_preprocess_islandora_objects(array &$variables) {
error_log('in upitt_solr_search_extras_preprocess_islandora_objects');
  $display = (empty($_GET['display'])) ? 'grid' : $_GET['display'];
  $grid_display = $display == 'grid';
  $list_display = !$grid_display;
  $query_params = drupal_get_query_parameters($_GET);
  error_log('in my themer');
  $variables['display_links'] = array(
    array(
      'title' => t('Grid view'),
      'href' => current_path(),
      'attributes' => array(
        'class' => array(
          $grid_display ? 'active' : '',
        ),
      ),
      'query' => array('display' => 'grid') + $query_params,
    ),
    array(
      'title' => t('List view'),
      'href' => current_path(),
      'attributes' => array(
        'class' => array(
          $list_display ? 'active' : '',
        ),
      ),
      'query' => array('display' => 'list') + $query_params,
    ),
  );
  // Pager.
  $objects = $variables['objects'];
  $limit = $variables['limit'];
  $page = pager_default_initialize(count($objects), $limit);
  $objects = array_slice($objects, $page * $limit, $limit);
  $variables['pager'] = theme('pager', array('quantity' => 10));

  $objects = array_map('islandora_objects_object_mapper', $objects);
  $theme = $grid_display ? 'islandora_objects_grid' : 'islandora_objects_list';
  $variables['content'] = theme($theme, array('objects' => $objects));
  $module_path = drupal_get_path('module', 'islandora');
  drupal_add_css("$module_path/css/islandora.objects.css");
}

/**
 * Prepares variables for islandora_objects_subset templates.
 *
 * A variant of "islandora_objects" which accepts a subset of object to theme.
 *
 * @see template_preprocess_islandora_objects()
 *
 * @param array $variables
 *   An associative array containing:
 *   - objects: An array of PIDs to render for the given page.
 *   - limit: An integer indicating the number of items per page, so we can
 *     render a pager.
 *   - total: An integer indicating the total number of items in the set, so
 *     can render a pager.
 *   - pager_element: An integer identifying which "pager" this display should
 *     use. Defaults to 0.
 *   - display: The default display to use when one is not provided in the URL.
 *     One of:
 *     - 'grid'
 *     - 'list'
 *   This function sets:
 *   - display_links: An array containing link structure, to allow the view to
 *     be toggled between a "grid" and "list" view.
 *   - pager: A renderable array for the pager.
 *   - content: A renderable array for the main content of the page.
 */
function upitt_solr_search_extras_preprocess_islandora_objects_subset(&$variables) {
error_log('in upitt_solr_search_extras_preprocess_islandora_objects_subset');
  $display = (empty($_GET['display'])) ? $variables['display'] : $_GET['display'];
  $grid_display = $display == 'grid';
  $list_display = !$grid_display;
  $query_params = drupal_get_query_parameters($_GET);

  // XXX: In l(), Drupal automatically adds the "active" class if it looks like
  // you are generating a link to the same page, based on the path and language.
  // Here, we use the "language" side of things to assert our links belong to a
  // non-existent language, so we can take control of adding our "active" class.
  $language_hack = new stdClass();
  $language_hack->language = 'a-non-existent-language';

  $variables['display_links'] = array(
    array(
      'title' => t('Grid view'),
      'href' => current_path(),
      'attributes' => array(
        'class' => array(
          $grid_display ? 'active' : '',
        ),
      ),
      'query' => array('display' => 'grid') + $query_params,
      'language' => $language_hack,
    ),
    array(
      'title' => t('List view'),
      'href' => current_path(),
      'attributes' => array(
        'class' => array(
          $list_display ? 'active' : '',
        ),
      ),
      'query' => array('display' => 'list') + $query_params,
      'language' => $language_hack,
    ),
  );

  $variables['pager'] = array(
    '#theme' => 'pager',
    '#element' => $variables['pager_element'],
  );
  $module_path = drupal_get_path('module', 'islandora');
  $variables['content'] = array(
    '#attached' => array(
      'css' => array(
        "$module_path/css/islandora.objects.css",
      ),
    ),
    '#theme' => $grid_display ? 'islandora_objects_grid' : 'islandora_objects_list',
    '#objects' => $variables['objects'],
  );
}

/**
 * Process variables for islandora_objects_subset templates.
 */
function upitt_solr_search_extras_process_islandora_objects_subset(&$variables) {
error_log('in upitt_solr_search_extras_process_islandora_objects_subset');
  pager_default_initialize($variables['total'], $variables['limit'], $variables['pager_element']);
  $variables['pager'] = drupal_render($variables['pager']);
  $variables['content']['#objects'] = array_map('islandora_objects_object_mapper', $variables['content']['#objects']);
  $variables['content'] = drupal_render($variables['content']);
}

