<?php

/**
 * @file
 * Theme hooks.
 */

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_subset(&$variables) {
  $islandora_object = menu_get_object('islandora_object', 2);
  module_load_include('inc', 'islandora', 'includes/metadata');
  if ($islandora_object) {
    $page_number = (empty($_GET['page'])) ? 0 : $_GET['page'];
    $page_size = (empty($_GET['pagesize'])) ? variable_get('islandora_basic_collection_page_size', '10') : $_GET['pagesize'];

    if (isset($islandora_object['TN_LARGE'])) {
      $collection_tn_url = url("islandora/object/{$islandora_object->id}/datastream/TN_LARGE/view");
      $params = array(
        'title' => $islandora_object->label,
        'alt' => $islandora_object->label,
        'path' => $collection_tn_url);
      $variables['collection_img'] = theme('image', $params);
    }
    $variables['collection_metadata'] = islandora_retrieve_metadata_markup($islandora_object);
  }
  $variables['display_links'] = array();
//  if (isset($_GET['display']) && $_GET['display'] <> 'grid') {
  $variables['pager'] = '';
//  }
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection_grid(&$variables, $hook) {
  $path = drupal_get_path('module', 'upitt_islandora_solr_search_extras');
  drupal_add_css("$path/css/solr_search_extras.css");
}

function upitt_islandora_solr_search_extras_preprocess_islandora_basic_collection(&$variables, $hook) {
  $path = drupal_get_path('module', 'upitt_islandora_solr_search_extras');
  drupal_add_css("$path/css/solr_search_extras.css");
  $variables['pager'] = '';
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects(&$variables) {
  $islandora_object = menu_get_object('islandora_object', 2);
  _get_solr_results($islandora_object, $variables);
  $item = menu_get_item();
  if (is_array($item)) {
    if ($item['path'] == 'islandora/object/%/pages') {
      $variables['display_links'] = array();
      $variables['pager'] = '';
    }
  }

}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_grid(&$variables) {
  $islandora_object = menu_get_object('islandora_object', 2);
  // Depending on the actual page, need to control whether or not the sidebar and other elements appear.
  $item = menu_get_item();
  $show_sidebar = TRUE;
  if (is_array($item)) {
    if ($item['path'] == 'islandora/object/%/pages') {
      $show_sidebar = FALSE;
    }
  }
  $variables['view_links'] = array();
  $variables['whamjack_sidebar'] = ''; // ($show_sidebar) ? _get_solr_sidebar_blocks() : '';
  _get_solr_results($islandora_object, $variables);
  $path = drupal_get_path('module', 'upitt_islandora_solr_search_extras');
  drupal_add_css("$path/css/solr_search_extras.css");
}

function upitt_islandora_solr_search_extras_preprocess_islandora_objects_list(&$variables) {
  $islandora_object = menu_get_object('islandora_object', 2);
  $variables['view_links'] = array();
  $variables['whamjack_sidebar'] = _get_solr_sidebar_blocks();
  _get_solr_results($islandora_object, $variables);
  $path = drupal_get_path('module', 'upitt_islandora_solr_search_extras');
  drupal_add_css("$path/css/solr_search_extras.css");
}

/**
 * Helper function to get the solr search results HTML for the various
 * templates that need it.  This will set the $variables['solr_search'] value.
 *
 * @param type $islandora_object
 * @param array $variables
 */
function _get_solr_results($islandora_object, &$variables) {
  if (isset($variables['solr_search']) && $variables['solr_search'] <> '') { return; }
  // Inspect the islandora_object - if it is a collection model object, then use 
  // RELS_EXT_isMemberOfCollection_uri_ms, else (for a book model), use RELS_EXT_isPageOf_uri_ms
  // for the SOLR query.
  $match_field = (in_array('islandora:bookCModel', $islandora_object->models)) ? 'RELS_EXT_isPageOf_uri_ms' : 'RELS_EXT_isMemberOfCollection_uri_ms';
  $solr_query = $match_field.':"info:fedora/' . $islandora_object->id . '"';
  $variables['solr_search'] = islandora_solr($solr_query);
}

function _get_solr_sidebar_blocks() {
  $sort_block = module_invoke('islandora_solr', 'block_view', 'sort');
  $facets_block = module_invoke('islandora_solr', 'block_view', 'basic_facets');
  $search_block = module_invoke('islandora_solr', 'block_view', 'advanced');
  // For some reason, the result of this block call is a different structure.
  $search_block['subject'] = 'Search';
  // Also, need to limit the terms and set the search value.
  $replace_terms = array();
  foreach ($search_block['content']['terms'] as $index => $search_term) {
    if (isset($search_term['field']['#value']) && $search_term['field']['#value'] == 'RELS_EXT_isMemberOfCollection_uri_ms') {
      // need to lookup the label of the current page's collection.
      $islandora_object = menu_get_object('islandora_object', 2);
      $search_term['search']['#value'] = isset($islandora_object) ? $islandora_object->label : '';
      if (isset($search_term['boolean'])) {
        unset($search_term['boolean']);
      }
      $replace_terms[] = $search_term;
    } 
  }
  $search_block['content']['terms'] = $replace_terms;
  $search_block['content'] = drupal_render($search_block); 

  return '
<div id="sidebar">
 <!-- div class="widget" -->
  <!-- div class="region region-sidebar" -->
        <div class="region region-sidebar">' .
_my_theme_solr_block($search_block, 'upitt_islandora_solr_search_extras', 'advanced') . 
_my_theme_solr_block($sort_block, 'upitt_islandora_solr_search_extras', 'sort') . '
' . _my_theme_solr_block($facets_block, 'upitt_islandora_solr_search_extras', 'basic_facets') . '
        </div>
  <!-- /div -->
 <!--/div -->
</div>
';
}

function _my_theme_solr_block($block, $block_module, $block_delta) {
  return '
<div id="' . drupal_html_id('block-islandora-solr-' . $block_delta) . '" class="block block-islandora-solr">
' . (isset($block['subject']) ? '
  <h2>' . $block['subject'] . '</h2>' : '') .
'  <div class="content">
    ' . $block['content'] .
'  </div>
</div> 
';
}
